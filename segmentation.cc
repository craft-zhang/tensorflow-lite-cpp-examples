/*
* Copyright 2017 The TensorFlow Authors. All Rights Reserved.
* Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <getopt.h>
#include <iostream>
#include <cstdarg>
#include <cstdio>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <limits>
#include <stdexcept>
#include <libgen.h>
#include <utility>
#include <sys/time.h>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <memory.h>

#include "model_utils.h"
#include "utils.h"
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/model.h"

using namespace cv;
using namespace std;

/*
 * labels for the segemantion
*/
string LABEL_NAMES [21] = {
    "background", "aeroplane", "bicycle", "bird", "boat", "bottle", "bus",
    "car", "cat", "chair", "cow", "diningtable", "dog", "horse", "motorbike",
    "person", "pottedplant", "sheep", "sofa", "train", "tv"
};

/*
 * Find the maximal arg index from the interfernce output
*/
Mat1b argMaxFromOutputTensor(const float *output_data, int height, int width, int num_label)
{
  Mat1b argMax(height, width);

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      float maxValue = 0;
      int maxIndex = 0;
      for (int k = 0; k < num_label; k++)
      {
        float output_val = output_data[y*width*num_label + x*num_label + k];
        if (output_val >= maxValue) {
          maxIndex = k;
          maxValue = output_val;
        }
      }
      argMax.at<uchar>(y, x) = maxIndex;
    }
  }

  return argMax;
}

/*
* Display frames: input (resized), segmentation map, and the overaly
*/
void DisplayFrames(char *display_win, int input_source, Mat &original_image, Mat &segmentation_colormap) {

    cv::Size s = original_image.size();
    int rows = s.height;
    int cols = s.width;

    Mat overlay_image;
    cv::addWeighted(original_image, 0.5, segmentation_colormap, 0.5, 0.0, overlay_image);

    cv::Mat win_mat(cv::Size(3*rows, cols), CV_8UC3);
    original_image.copyTo(win_mat(cv::Rect(0, 0, rows, cols)));
    segmentation_colormap.copyTo(win_mat(cv::Rect(rows, 0, rows, cols)));
    overlay_image.copyTo(win_mat(cv::Rect(rows*2, 0, rows, cols)));

    cv::imshow(display_win, win_mat);

    if (input_source == 0)
    {
      char c=(char)waitKey(0);
    } else
    {
      char c=(char)waitKey(1);
    }
}

/*
* Display command line usage
*/
void display_usage() {
   std:cout
      << "tflite_segmentation\n"
      << "--tflite_model, -m: model_name.tflite\n"
      << "--input_src, -r: [0|1|2] input source: image 0, video 1, camera 2\n"
      << "--input_path, -i: path of the input image/video or video port for camera, e.g., 1 for /dev/video1\n"
      << "--frame_cnt, -c: the number of frames to be used\n"
      << "--input_mean, -b: input mean\n"
      << "--input_std, -s: input standard deviation\n"
      << "--profiling, -p: [0|1], profiling or not\n"
      << "--threads, -t: number of threads\n"
      << "\n";
}

/*
* Main function
*/
int main(int argc, char** argv) {
// Set the defaults which can be modified from command line
  std::string model_path = "./deeplabv3_257_mv_gpu.tflite";
  std::string input_path = "./bird_segmentation.bmp";
  eInputType input_source = INPUT_Image;
  int frame_cnt   = 1;
  int num_threads = 1;
  float input_mean = 127.5f;
  float input_std  = 127.5f;
  bool  profiling = false;

  int c;
  while (1) {
    static struct option long_options[] = {
	{"frame_cnt", required_argument, nullptr, 'c'},
        {"input_src", required_argument, nullptr, 'r'},
        {"input_path", required_argument, nullptr, 'i'},
        {"tflite_model", required_argument, nullptr, 'm'},
        {"profiling", required_argument, nullptr, 'p'},
        {"threads", required_argument, nullptr, 't'},
        {"input_mean", required_argument, nullptr, 'b'},
        {"input_std", required_argument, nullptr, 's'},
        {nullptr, 0, nullptr, 0}};

    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long(argc, argv,
                    "b:c:i:m:p:r:s:t:h", long_options,
                    &option_index);

    /* Detect the end of the options. */
    if (c == -1) break;

    switch (c) {
      case 'b':
        input_mean = strtod(optarg, nullptr);
        break;
      case 'c':
        frame_cnt = strtol(optarg, nullptr, 10);
        break;
      case 'i':
        input_path = optarg;
        break;
      case 'm':
        model_path = optarg;
        break;
      case 'p':
        profiling = strtol(optarg, nullptr, 10);
        break;
      case 'r':
        input_source = (eInputType)strtol(optarg, nullptr, 10);
        break;
      case 's':
        input_std = strtod(optarg, nullptr);
        break;
      case 't':
        num_threads = strtol(optarg, nullptr, 10);
        break;
      case 'h':
        display_usage();
        exit(-1);
      default:
        exit(-1);
    }
  }

  std::cout << "Loading model... " << std::endl;

  // Read model.
  std::unique_ptr<tflite::FlatBufferModel> model =
      tflite::FlatBufferModel::BuildFromFile(model_path.c_str());
  if (model == nullptr) {
    std::cerr << "Fail to build FlatBufferModel from file: " << model_path
              << std::endl;
    std::abort();
  }

  // Build interpreter.
  std::unique_ptr<tflite::Interpreter> interpreter =
      tflite_example::BuildTfliteInterpreter(*model, num_threads);

  // Get input dimension from the input tensor metadata
  // assuming one input only
  const auto& required_shape = tflite_example::GetInputShape(*interpreter, 0);
  int wanted_height = required_shape[0];
  int wanted_width = required_shape[1];
  int wanted_channels = required_shape[2];
  int input_number_of_pixels = wanted_height*wanted_width*wanted_channels;

  // Setup input
  Mat input_image;
  VideoCapture cap;
  if (! SetupInput(input_source, input_path, cap, input_image)) {
    std::abort();
  }

  // Setup display
  char display_win[160];
  sprintf(display_win, "Segmentation");
  SetupLiveDisplay(display_win);

  std::cout << "Running inference... " << std::endl;

  int frame_index = 0;
  // Processing loop for preparing the input, running inference, and reporting classification result
  while(frame_cnt > 0) {
    // Collect the frame in NHWC with the wanted size
    std::vector<uint8_t> input_frame;
    CollectFrames(input_frame, input_source, cap, input_image,
                  wanted_height, wanted_width, wanted_channels);

    if (input_frame.empty()) {
      continue;
    }

    // Prepare the input for the inference
    int input = interpreter->inputs()[0];
    switch (interpreter->tensor(input)->type) {
      case kTfLiteFloat32:
        PrepareInput<float>(interpreter->typed_tensor<float>(input), input_frame,
                    input_number_of_pixels, true, input_mean, input_std);
        break;
      case kTfLiteUInt8:
	PrepareInput<uint8_t>(interpreter->typed_tensor<uint8_t>(input), input_frame,
                    input_number_of_pixels, false, input_mean, input_std);
        break;
      default:
        cout << "cannot handle input type " << interpreter->tensor(input)->type << " yet" << std::endl ;
        exit(-1);
   }

    // Running the inference
    struct timeval start_time, stop_time;
    gettimeofday(&start_time, nullptr);
    const auto& result = tflite_example::RunInference(interpreter.get());
    gettimeofday(&stop_time, nullptr);

    if (profiling) {
      std::cout << "Inference time for frame " << frame_index << ": "
                << (get_us(stop_time) - get_us(start_time)) / 1000
                << " ms" << std::endl;
    }

    // Report the inference output
    // Get the output shape
    const auto& output_shape = tflite_example::GetOutputShape(*interpreter, 0);
    int output_height = output_shape[0];
    int output_width = output_shape[1];
    int output_channels = output_shape[2];

    // Find the maximal arg index of the output
    const Mat1b& argMaxOutput = argMaxFromOutputTensor(result.data(), output_height, output_width, output_channels);

    // Create the segmentation mask with opencv color map
    argMaxOutput *= (255/output_channels);
    Mat segmentation_colormap;
    applyColorMap(argMaxOutput, segmentation_colormap, COLORMAP_HSV);

    Mat resized_input_image;
    cv::resize(input_image, resized_input_image, Size(wanted_width, wanted_height));

    // Display frame with the segmentation mask
    DisplayFrames(display_win, input_source, resized_input_image, segmentation_colormap);

    frame_cnt--;
    frame_index++;
  }

  std::cout << "Segmenation completes! " << std::endl;

  return 0;
}
