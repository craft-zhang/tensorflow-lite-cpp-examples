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

/*
rm -f classification/tflite_classification && make -f Makefile-rv

qemu-riscv64 classification/tflite_classification -m \
classification/imagenet_mobilenet_v1_100_224_classification.tflite -i \
classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1
# label: Blenheim spaniel with probability 18.3755

qemu-riscv64 classification/tflite_classification -m \
classification/imagenet_mobilenet_v2_100_224_classification.tflite -i \
classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1
# label: Blenheim spaniel with probability 9.8589

qemu-riscv64 classification/tflite_classification -m \
classification/imagenet_inception_v1_classification_5.tflite -i \
classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1
# label: Blenheim spaniel with probability 10.9008

qemu-riscv64 classification/tflite_classification -m \
classification/imagenet_inception_v2_classification_5.tflite -i \
classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1
# label: Blenheim spaniel with probability 11.0233 有bug

qemu-riscv64 classification/tflite_classification_arm -m \
classification/imagenet_inception_v3_classification_5.tflite -i \
classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1
# label: Blenheim spaniel with probability 22.116

qemu-riscv64 classification/tflite_classification -m \
classification/imagenet_resnet_v1_50_classification_5.tflite -i \
classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1
# label: Blenheim spaniel with probability 16.8781

qemu-riscv64 classification/tflite_classification -m \
classification/imagenet_resnet_v2_50_classification_5.tflite -i \
classification/dog.jpg -l classification/labels.txt -c 1 -b 0 -s 255 -t 1
# label: Blenheim spaniel with probability 19.5378

*/

#include <getopt.h>
#include <libgen.h>
#include <memory.h>
#include <sys/time.h>

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

#include "model_utils.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "tensorflow/lite/delegates/xnnpack/xnnpack_delegate.h"
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/model.h"
#include "utils.h"

using namespace cv;
using namespace std;

/*
 * Iterate through all the lines in file and
 * put them in given vector
 */
bool getFileContent(std::string fileName, std::vector<std::string> &vecOfStrs) {
  // Open the File
  std::ifstream in(fileName.c_str());
  // Check if object is valid
  if (!in) {
    std::cerr << "Cannot open the File : " << fileName << std::endl;
    return false;
  }
  std::string str;
  // Read the next line from File untill it reaches the end.
  while (std::getline(in, str)) {
    // Line contains string of length > 0 then save it in vector
    if (str.size() > 0)
      vecOfStrs.push_back(str);
  }
  // Close The File
  in.close();
  return true;
}

/*
 * Display frames with the classification result
 */
void DisplayFrames(char *display_win, int input_source, Mat &show_image,
                   std::string &output_labels) {
  // overlay the display window
  cv::putText(show_image, output_labels.c_str(),
              cv::Point(32, 32),              // Coordinates
              cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
              1.25,                           // Scale. 2.0 = 2x bigger
              cv::Scalar(0, 0, 0),            // Color
              1.5,                            // Thickness
              8);                             // Line type
  cv::imshow(display_win, show_image);

  if (input_source == INPUT_Image)
    char c = (char)waitKey(0);
  else
    char c = (char)waitKey(1);
}

/*
 * Display command line usage
 */
void display_usage() {
std:
  cout << "tflite_classification\n"
       << "--frame_cnt, -c: the number of frames to be used\n"
       << "--input_path, -i: path of the input image/video or video port for "
          "camera, e.g., 1 for /dev/video1\n"
       << "--labels, -l: labels for the model\n"
       << "--tflite_model, -m: model_name.tflite\n"
       << "--profiling, -p: [0|1], profiling or not\n"
       << "--input_src, -r: [0|1|2] input source: image 0, video 1, camera 2\n"
       << "--input_mean, -b: input mean\n"
       << "--input_std, -s: input standard deviation\n"
       << "--threads, -t: number of threads\n"
       << "--feature_copy, -f: feature copy to tcm\n"
       << "--weight_copy, -w: weight copy to tcm\n"
       << "--profile, -d: profile all layer\n"
       << "--conv_profile, -P: profile convlution\n"
       << "--freq, -F: cpu freq MHz\n"
       << "--affinity, -a: process affinity\n"
       << "--only_conv, -C: only run convlution\n"
       << "--only_misc, -M: only run other op except convlution\n"
       << "\n";
}

#ifdef __cplusplus
extern "C" {
#endif
extern size_t packed_weight_in_byte;
extern size_t packed_feature_in_byte;

extern size_t packed_weight_access_in_byte;
extern size_t packed_feature_access_in_byte;

extern bool PROFILE;
extern bool CONV_PROFILE;

extern long FREQ;

extern bool FEA_CPY2TCM;
extern bool FILTER_CPY2TCM;

extern bool ONLY_CONV;
extern bool ONLY_MISC;

extern long ELAPSEDTIME;
#ifdef __cplusplus
}
#endif

//  (input - mean) / std
/*
 * Main function
 */
int main(int argc, char **argv) {
  // Set the defaults which can be modified from command line
  std::string model_path = "./mobilenet_v1_1.0_224.tflite";
  std::string input_path = "./grace_hopper.bmp";
  std::string label_path = "./labels.txt";
  eInputType input_source = INPUT_Image;
  int frame_cnt = 1;
  int num_threads = 1;
  float input_mean = 127.5f;
  float input_std = 127.5f;
  bool profiling = false;

  int c;
  while (1) {
    static struct option long_options[] = {
        {"frame_cnt", required_argument, nullptr, 'c'},
        {"input_path", required_argument, nullptr, 'i'},
        {"labels", required_argument, nullptr, 'l'},
        {"tflite_model", required_argument, nullptr, 'm'},
        {"profiling", required_argument, nullptr, 'p'},
        {"input_src", required_argument, nullptr, 'r'},
        {"input_mean", required_argument, nullptr, 'b'},
        {"input_std", required_argument, nullptr, 's'},
        {"threads", required_argument, nullptr, 't'},
        {"feature_copy", required_argument, nullptr, 'f'},
        {"weight_copy", required_argument, nullptr, 'w'},
        {"profile", required_argument, nullptr, 'd'},
        {"conv_profile", required_argument, nullptr, 'P'},
        {"freq", required_argument, nullptr, 'F'},
        {"affinity", required_argument, nullptr, 'a'},
        {"only_conv", required_argument, nullptr, 'C'},
        {"only_misc", required_argument, nullptr, 'M'},
        {nullptr, 0, nullptr, 0}};

    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long(argc, argv, "c:i:l:m:p:r:b:s:t:f:w:d:P:F:a:C:M:h",
                    long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1)
      break;

    switch (c) {
    case 'c':
      frame_cnt = strtol(optarg, nullptr, 10);
      break;
    case 'i':
      input_path = optarg;
      break;
    case 'l':
      label_path = optarg;
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
    case 'b':
      input_mean = strtod(optarg, nullptr);
      break;
    case 's':
      input_std = strtod(optarg, nullptr);
      break;
    case 't':
      num_threads = strtol(optarg, nullptr, 10);
      break;
    case 'f':
      FEA_CPY2TCM = strtol(optarg, nullptr, 10);
      break;
    case 'w':
      FILTER_CPY2TCM = strtol(optarg, nullptr, 10);
      break;
    case 'd':
      PROFILE = strtol(optarg, nullptr, 10);
      break;
    case 'P':
      CONV_PROFILE = strtol(optarg, nullptr, 10);
      break;
    case 'F':
      FREQ = strtol(optarg, nullptr, 10);
      break;
    case 'a': {
      char *core_id_str = strtok(optarg, ",");
      cpu_set_t mask;
      CPU_ZERO(&mask);
      while (core_id_str) {
        long core_id = strtol(core_id_str, nullptr, 10);
        if (core_id > -1) {
          CPU_SET(core_id, &mask);
          fprintf(stderr, "set affinity to %d!\n", core_id);
        } else {
          fprintf(stderr, "noaffinity set!\n");
        }
        core_id_str = strtok(NULL, ",");
      }
      int result = sched_setaffinity(0, sizeof(mask), &mask);
      if (result == 0) {
        fprintf(stderr, "set process affinity suc!\n");
      } else {
        fprintf(stderr, "set process affinity err %d!\n", result);
      }
    } break;
    case 'C':
      ONLY_CONV = strtol(optarg, nullptr, 10);
      break;
    case 'M':
      ONLY_MISC = strtol(optarg, nullptr, 10);
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
  std::cout << "Loading model done!" << std::endl;

  // Build interpreter.
  // Create TfLite Interpreter
  // std::unique_ptr<tflite::Interpreter> interpreter;
  // std::cout << "Loading model done!" << std::endl;
  // // IMPORTANT: initialize options with
  // // TfLiteXNNPackDelegateOptionsDefault() for API-compatibility with future
  // // extensions of the TfLiteXNNPackDelegateOptions structure.
  // TfLiteXNNPackDelegateOptions xnnpack_options =
  //     TfLiteXNNPackDelegateOptionsDefault();
  // xnnpack_options.num_threads = num_threads;

  // TfLiteDelegate *xnnpack_delegate =
  //     TfLiteXNNPackDelegateCreate(&xnnpack_options);
  // if (interpreter->ModifyGraphWithDelegate(xnnpack_delegate) != kTfLiteOk) {
  //   // Report error and fall back to another delegate, or the default backend
  // }

  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
  std::unique_ptr<tflite::Interpreter> interpreter =
      tflite_example::BuildTfliteInterpreter(*model, num_threads);
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;

  // Get input dimension from the input tensor metadata
  // assuming one input only
  const auto &required_shape = tflite_example::GetInputShape(*interpreter, 0);
  int wanted_height = required_shape[0];
  int wanted_width = required_shape[1];
  int wanted_channels = required_shape[2];
  int input_number_of_pixels = wanted_height * wanted_width * wanted_channels;

  // Setup input
  Mat input_image;
  VideoCapture cap;
  if (!SetupInput(input_source, input_path, cap, input_image)) {
    std::abort();
  }

  // Setup display
  // char display_win[160];
  // sprintf(display_win, "Classification");
  // SetupLiveDisplay(display_win);

  // Setup labels
  std::vector<std::string> labels;
  bool labels_ok = false;

  labels_ok = getFileContent(label_path, labels);
  if (!labels_ok) {
    std::cerr << "Fail to read the label file: " << label_path << std::endl;
    std::abort();
  }

  std::cout << "Running inference... " << std::endl;

  int frame_index = 0;
  // Processing loop for preparing the input, running inference, and reporting
  // classification result
  while (frame_cnt > 0) {
    // Collect the frame in NHWC with the wanted size
    std::vector<uint8_t> input_frame;
    std::cout << "HWC=" << wanted_height << "-" << wanted_width << "-"
              << wanted_channels << std::endl;
    CollectFrames(input_frame, input_source, cap, input_image, wanted_height,
                  wanted_width, wanted_channels);

    if (input_frame.empty()) {
      continue;
    }

    // Prepare the input for the inference
    int input = interpreter->inputs()[0];
    switch (interpreter->tensor(input)->type) {
    case kTfLiteFloat32:
      std::cout << "kTfLiteFloat32" << std::endl;
      PrepareInput<float>(interpreter->typed_tensor<float>(input), input_frame,
                          input_number_of_pixels, true, input_mean, input_std);
      break;
    case kTfLiteUInt8:
      std::cout << "kTfLiteUInt8" << std::endl;
      PrepareInput<uint8_t>(interpreter->typed_tensor<uint8_t>(input),
                            input_frame, input_number_of_pixels, false,
                            input_mean, input_std);
      break;
    case kTfLiteInt8:
      std::cout << "kTfLiteInt8" << std::endl;
      PrepareInput<int8_t>(interpreter->typed_tensor<int8_t>(input),
                           input_frame, input_number_of_pixels, false,
                           input_mean, input_std);
      break;
    default:
      cout << "cannot handle input type " << interpreter->tensor(input)->type
           << " yet" << std::endl;
      exit(-1);
    }

    // Running the inference
    double inference_time_ms;
    const auto &result =
        tflite_example::RunInference(interpreter.get(), inference_time_ms);

    if (profiling) {
      std::cout << "Inference time for frame " << frame_index << ": "
                << inference_time_ms << " ms"
                << " XNNPACKrun: " << ELAPSEDTIME << "ms" << std::endl;
    }
    ELAPSEDTIME = 0;
    // Report the inference output
    std::string last_label = "None";
    int argmax = -1;

    // Find the maxiaml probablity and its corresponding label
    auto it = std::max_element(result.begin(), result.end());
    argmax = std::distance(result.begin(), it);

    float prob_threshold = 0.2;
    if ((argmax < labels.size()) && (*it > prob_threshold)) {
      std::cout << "label: " << labels[argmax] << " with probability " << *it
                << std::endl;
      last_label = labels[argmax];
    }

    // Display frame with the classification result
    // DisplayFrames(display_win, input_source, input_image, last_label);

    frame_cnt--;
    frame_index++;
  }

  std::cout << "Classification complete ! " << std::endl;

#ifdef MEM_PROFILE
  std::cout << "packed_weight_in_byte = " << packed_weight_in_byte << std::endl
            << "packed_feature_in_byte = " << packed_feature_in_byte
            << std::endl
            << "packed_weight_access_in_byte = " << packed_weight_access_in_byte
            << std::endl
            << "packed_feature_access_in_byte = "
            << packed_feature_access_in_byte << std::endl;
#endif

  // IMPORTANT: release the interpreter before destroying the
  // delegate
  interpreter.reset();
  // TfLiteXNNPackDelegateDelete(xnnpack_delegate);

  return 0;
}
