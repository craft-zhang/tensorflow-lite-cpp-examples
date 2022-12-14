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

#include "yolov5.h"

void YOLOV5::getLabelsName(std::string path,
                           std::vector<std::string> &labelNames) {
  // Open the File
  std::ifstream in(path.c_str());
  // Check if object is valid
  if (!in)
    throw std::runtime_error("Can't open ");
  std::string str;
  // Read the next line from File until it reaches the end.
  while (std::getline(in, str)) {
    // Line contains string of length > 0 then save it in vector
    if (str.size() > 0)
      labelNames.push_back(str);
  }
  // Close The File
  in.close();
}

void YOLOV5::loadModel(const std::string path) {
  _model = tflite::FlatBufferModel::BuildFromFile(path.c_str());
  if (!_model) {
    std::cout << "\nFailed to load the model.\n" << std::endl;
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    exit(1);
  } else {
    std::cout << "\nModel loaded successfully.\n";
  }
  tflite::ops::builtin::BuiltinOpResolver resolver;
  tflite::InterpreterBuilder(*_model, resolver)(&_interpreter);
  TfLiteStatus status = _interpreter->AllocateTensors();
  if (status != kTfLiteOk) {
    std::cout << "\nFailed to allocate the memory for tensors.\n" << std::endl;
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    exit(1);
  } else {
    std::cout << "\nMemory allocated for tensors.\n";
  }

  // input information
  _input = _interpreter->inputs()[0];
  TfLiteIntArray *dims = _interpreter->tensor(_input)->dims;
  _in_height = dims->data[1];
  _in_width = dims->data[2];
  _in_channels = dims->data[3];
  _in_type = _interpreter->tensor(_input)->type;
  _input_f32 = _interpreter->typed_tensor<float_t>(_input);
  std::cout << "YOLO Model Input Shape:[1][" << _in_height << "][" << _in_width
            << "][" << _in_channels << "]\n";
  _interpreter->SetNumThreads(_n_threads);
}

void YOLOV5::preprocess(cv::Mat &image) {
  if (image.data) {
    std::cout << "Cvt Color Space to RGB\n";
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    std::cout << "Resize to fit input Shape\n";
    cv::resize(image, image, cv::Size(_in_height, _in_width));
    // cv::imwrite("image.jpg", image);
    // image.convertTo(image, CV_32FC3);
  } else {
    std::cout << "input image is empty!\n";
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    exit(-1);
  }
}

template <typename T> void YOLOV5::fill(T *in, cv::Mat &src) {
  if (in != NULL && src.data != NULL) {
    uchar *ptr = src.data;
    for (size_t i = 0; i < src.rows; i++) {
      for (size_t j = 0; j < src.cols * 3; j++) {
        in[i * src.cols * 3 + j] = ((float_t)(ptr[j]) - _mean) / _std;
      }
      ptr += src.step;
    }
  } else {
    std::cout << "input image or input tensor is empty!\n";
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    exit(-1);
  }
}

std::vector<std::vector<float>> YOLOV5::tensorToVector2D() {
  int out = _interpreter->outputs()[0];
  TfLiteIntArray *out_dims = _interpreter->tensor(out)->dims;
  int out_batch = out_dims->data[0];
  _out_row = out_dims->data[1];
  _out_colum = out_dims->data[2];
  // class number + 5 ---> 85  bbox cond class
  std::cout << "YOLO Model Output Shape:[" << out_batch << "][" << _out_row
            << "][" << _out_colum << "]\n";

  TfLiteTensor *pOutputTensor = NULL;
  if (_interpreter->outputs().size() == 1) {
    pOutputTensor = _interpreter->tensor(_interpreter->outputs()[0]);
  } else {
    std::cout << "yolov5 don't support this model!\n";
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    exit(-1);
  }

  std::vector<std::vector<float>> v;

  if (pOutputTensor->type == kTfLiteInt8) {
    auto scale = pOutputTensor->params.scale;
    auto zero_point = pOutputTensor->params.zero_point;
    for (int32_t i = 0; i < _out_row; i++) {
      std::vector<float> _tem;
      for (int j = 0; j < _out_colum; j++) {
        float val_float =
            (((int32_t)pOutputTensor->data.int8[i * _out_colum + j]) -
             zero_point) *
            scale;
        _tem.push_back(val_float);
      }
      v.push_back(_tem);
    }
  } else if (pOutputTensor->type == kTfLiteFloat32) {
    for (int32_t i = 0; i < _out_row; i++) {
      std::vector<float> _tem;
      for (int j = 0; j < _out_colum; j++) {
        float val_float = pOutputTensor->data.f[i * _out_colum + j];
        _tem.push_back(val_float);
      }
      v.push_back(_tem);
    }
  } else {
    std::cout << "Unsupported output type!\n";
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    exit(-1);
  }
  return v;
}

void YOLOV5::nonMaximumSupprition(std::vector<std::vector<float>> &predV,
                                  std::vector<cv::Rect> &boxes,
                                  std::vector<float> &confidences,
                                  std::vector<int> &classIds,
                                  std::vector<int> &indices)

{
  std::vector<cv::Rect> boxesNMS;
  std::vector<float> scores;
  double confidence;
  cv::Point classId;

  for (int i = 0; i < _out_row; i++) {
    if (predV[i][4] > _conf_threshold) {
      int left = (predV[i][0] - predV[i][2] / 2) * _img_width;
      int top = (predV[i][1] - predV[i][3] / 2) * _img_height;
      int w = predV[i][2] * _img_width;
      int h = predV[i][3] * _img_height;

      for (int j = 5; j < _out_colum; j++) {
        // # conf = obj_conf * cls_conf
        scores.push_back(predV[i][j] * predV[i][4]);
      }

      cv::minMaxLoc(scores, 0, &confidence, 0, &classId);

      scores.clear();

      if (confidence > _conf_threshold * _conf_threshold) {
        boxes.push_back(cv::Rect(left, top, w, h));
        confidences.push_back(confidence);
        classIds.push_back(classId.x);
        boxesNMS.push_back(cv::Rect(left, top, w, h));
      }
    }
  }
  cv::dnn::NMSBoxes(boxesNMS, confidences, _conf_threshold, _nms_threshold,
                    indices);
}

void YOLOV5::run(cv::Mat &frame, Prediction &out_pred) {
  do {
    if (!frame.data) {
      std::cout << "input image is empty!\n";
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;
      exit(-1);
    }

    _img_height = frame.rows;
    _img_width = frame.cols;

    preprocess(frame);
    fill(_input_f32, frame);

    // Inference
    std::cout << "Run inference!!\n";
    TfLiteStatus status = _interpreter->Invoke();
    if (status != kTfLiteOk) {
      std::cout << "\nFailed to run inference!!\n";
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;
      exit(-1);
    }

    for (size_t i = 0; i < _interpreter->outputs().size(); i++) {
      TfLiteIntArray *out_dims =
          _interpreter->tensor(_interpreter->outputs()[i])->dims;
      int out_batch = out_dims->data[0];
      int out_row = out_dims->data[1];
      int out_colum = out_dims->data[2];
      int out_channel = out_dims->data[3];
      std::cout << "YOLO Model Output Shape:[" << out_batch << "][" << out_row
                << "][" << out_colum << "][" << out_channel << "]\n";
    }

    std::vector<std::vector<float>> predV = tensorToVector2D();

    std::vector<int> indices;
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    nonMaximumSupprition(predV, boxes, confidences, classIds, indices);

    for (int i = 0; i < indices.size(); i++) {
      out_pred.boxes.push_back(boxes[indices[i]]);
      out_pred.scores.push_back(confidences[indices[i]]);
      out_pred.labels.push_back(classIds[indices[i]]);
    }
  } while (0);
};