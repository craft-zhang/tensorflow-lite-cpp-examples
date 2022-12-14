/*
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

#include "utils.h"

#include <iostream>

using namespace cv;
using namespace std;

/*
 * Setup input from image, video, and camera
 */
bool SetupInput(eInputType input_source, string input_path, VideoCapture &cap,
                Mat &input_image) {
  if (input_source == INPUT_Image) {
    // Read image input
    input_image = imread(input_path);
    if (!input_image.data) // Check for invalid input
    {
      cout << "Could not open or find the image" << std::endl;
      return false;
    }
    std::cout << "Image input: " << input_path.c_str() << std::endl;
    return true;
  } else if (input_source == INPUT_Camera) {
    // Read camera input
    int video_port = atoi(input_path.c_str());
    cap.open(video_port);
    // Setting the capture resolution
    cap.set(CAP_PROP_FRAME_WIDTH, 352);
    cap.set(CAP_PROP_FRAME_HEIGHT, 288);
    const double fps = cap.get(CAP_PROP_FPS);
    const int width = cap.get(CAP_PROP_FRAME_WIDTH);
    const int height = cap.get(CAP_PROP_FRAME_HEIGHT);
    std::cout << "Capture camera with " << fps << " fps, " << width << "x"
              << height << " px" << std::endl;
  } else if (input_source == INPUT_Video) {
    // Read video input
    std::cout << "Video input clip: " << input_path.c_str() << std::endl;
    cap.open(input_path);
    const double fps = cap.get(CAP_PROP_FPS);
    const int width = cap.get(CAP_PROP_FRAME_WIDTH);
    const int height = cap.get(CAP_PROP_FRAME_HEIGHT);
    std::cout << "Clip with " << fps << " fps, " << width << "x" << height
              << " px" << std::endl;
  } else {
    std::cout << "Input source " << input_source << " is not supported!!!"
              << std::endl;
    return false;
  }

  if (!cap.isOpened()) {
    std::cout << "Video or camera input not opened!" << std::endl;
    return false;
  }

  return true;
}

/*
 * Retrieve frame, resize, and record in NHWC format
 */
void CollectFrames(std::vector<uint8_t> &output, int input_source,
                   cv::VideoCapture &cap, cv::Mat &in_image, int width,
                   int height, int channels) {
  // Retrieve frame from video/camera input, and resize it to the wanted size;
  // For image input, frame has been read in in_image, so just resize it.
  bool frame_retrieved = false;
  Mat image;
  if (input_source != INPUT_Image) {
    if (cap.grab()) {
      if (cap.retrieve(in_image)) {
        if (input_source == INPUT_Camera) { // Crop central square portion
          int loc_xmin = (in_image.size().width - in_image.size().height) /
                         2; // Central position
          int loc_ymin = 0;
          int loc_w = in_image.size().height; // Set the width to height to get
                                              // the square cropping
          int loc_h = in_image.size().height;
          // do cropping and resize
          cv::resize(in_image(Rect(loc_xmin, loc_ymin, loc_w, loc_h)), image,
                     Size(width, height));
        } else {
          cv::resize(in_image, image, Size(width, height));
        }
        frame_retrieved = true;
      }
    } else {
      // rewind for video input
      if (input_source == INPUT_Video) {
        cap.set(CAP_PROP_POS_FRAMES, 0);
      }
    }
  } else {
    cv::resize(in_image, image, Size(width, height));
    frame_retrieved = true;
  }

  if (!frame_retrieved)
    return;

  Mat *spl = new Mat[channels];
  split(image, spl);

  // Read the frame in NHWC format
  output.resize(height * width * channels);
  for (int c = 0; c < channels; c++) {
    const unsigned char *data = spl[c].ptr();
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        output[channels * (y * width + x) + (channels - 1) - c] =
            (uint8_t)data[y * width + x];
      }
    }
  }
}

/*
 * Display callback function
 */
void displayCallBackFunc(int event, int x, int y, int flags, void *userdata) {
  if (event == EVENT_RBUTTONDOWN) {
    std::cout << "Right button of the mouse is clicked - position (" << x
              << ", " << y << ")"
              << " ... prepare to exit!" << std::endl;
    exit(0);
  }
}

/*
 * Setup display
 */
void SetupLiveDisplay(char *display_win) {
  // namedWindow(display_win, WINDOW_AUTOSIZE | CV_GUI_NORMAL);
  // set the callback function for any mouse event
  // setMouseCallback(display_win, displayCallBackFunc, NULL);
}
