/*
 * zhangdanfeng 2022
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
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/model.h"
#include "utils.h"
#include "yolov3.h"
#include "yolov5.h"

using namespace cv;
using namespace std;

/*
qemu-riscv64 detection/tflite_detection -m \
detection/yolov5s_ultralytics_640_quantized.tflite -i detection/bus.jpg -l \
detection/labels.txt -c 1 -b 0 -s 255 -t 1 -v 5

qemu-riscv64 detection/tflite_detection -m \
detection/yolov3_keras_416_quantized.tflite -i detection/bus.jpg -l \
detection/labels.txt -c 1 -b 0 -s 255 -t 1 -v 3
*/

/*
 * Display command line usage
 */
void display_usage() {
std:
  cout << "tflite_detection\n"
       << "--tflite_model, -m: model_name.tflite\n"
       << "--label_file, -l: label_file\n"
       << "--input_src, -r: [0|1|2] input source: image 0, video 1, camera 2\n"
       << "--input_path, -i: path of the input image/video or video port for "
          "camera, e.g., 1 for /dev/video1\n"
       << "--frame_cnt, -c: the number of frames to be used\n"
       << "--input_mean, -b: input mean\n"
       << "--input_std, -s: input standard deviation\n"
       << "--profiling, -p: [0|1], profiling or not\n"
       << "--threads, -t: number of threads\n"
       << "--model-version, -v: yolo version\n"
       << "\n";
}

/*
 * Main function
 */
int main(int argc, char **argv) {
  // Set the defaults which can be modified from command line
  std::string model_path = "yolov5s_ultralytics_640_quantized.tflite";
  std::string label_path = "labels.txt";
  std::string input_path = "grace_hopper.bmp";
  eInputType input_source = INPUT_Image;
  int yolo_version = 5;
  int frame_cnt = 1;
  int num_threads = 1;
  float input_mean = 0.f;
  float input_std = 1.f;
  bool profiling = true;

  int c;
  while (1) {
    static struct option long_options[] = {
        {"frame_cnt", required_argument, nullptr, 'c'},
        {"input_src", required_argument, nullptr, 'r'},
        {"input_path", required_argument, nullptr, 'i'},
        {"tflite_model", required_argument, nullptr, 'm'},
        {"label_file", required_argument, nullptr, 'l'},
        {"profiling", required_argument, nullptr, 'p'},
        {"threads", required_argument, nullptr, 't'},
        {"input_mean", required_argument, nullptr, 'b'},
        {"input_std", required_argument, nullptr, 's'},
        {"--model-version", required_argument, nullptr, 'v'},
        {nullptr, 0, nullptr, 0}};

    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long(argc, argv, "b:c:i:m:l:p:r:s:t:v:h", long_options,
                    &option_index);

    /* Detect the end of the options. */
    if (c == -1)
      break;

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
    case 'l':
      label_path = optarg;
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
    case 'v':
      yolo_version = strtol(optarg, nullptr, 10);
      break;
    case 'h':
      display_usage();
      exit(-1);
    default:
      exit(-1);
    }
  }

  YOLOV5 *model = NULL;
  if (yolo_version == 3) {
    model = new YOLOV3;
  } else {
    model = new YOLOV5;
  }
  if (!model) {
    exit(-1);
  }

  Prediction out_pred;
  std::vector<std::string> labelNames;

  std::cout << "Loading model... " << std::endl;

  // Read model.
  model->loadModel(model_path);

  model->getLabelsName(label_path, labelNames);
  std::cout << "\nLabel Count: " << labelNames.size() << "\n" << std::endl;

  // Setup input
  Mat input_image;
  VideoCapture cap;
  if (!SetupInput(input_source, input_path, cap, input_image)) {
    std::abort();
  }

  std::cout << "Running inference... " << std::endl;

  auto start = std::chrono::high_resolution_clock::now();
  // Predict on the input image
  cv::Mat show_image;
  input_image.copyTo(show_image);
  model->run(input_image, out_pred);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "\nModel run time 'milliseconds': " << duration.count() << "\n"
            << std::endl;

  // add the bbox to the image and save it
  auto boxes = out_pred.boxes;
  auto scores = out_pred.scores;
  auto labels = out_pred.labels;

  for (int i = 0; i < boxes.size(); i++) {
    auto box = boxes[i];
    auto score = scores[i];
    auto label = labels[i];
    cv::rectangle(show_image, box, cv::Scalar(255, 0, 0), 2);
    cv::putText(show_image, labelNames[label], cv::Point(box.x, box.y),
                cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(255, 255, 255), 1,
                cv::LINE_AA);
  }

  cv::imwrite("out.png", show_image);

  std::cout << "detection completes! " << std::endl;
  delete model;
  return 0;
}
