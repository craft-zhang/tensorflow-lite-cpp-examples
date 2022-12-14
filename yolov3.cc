#include "yolov3.h"

std::vector<std::vector<float>> YOLOV3::tensorToVector2D() {
  std::vector<std::vector<float>> v;
  if (_interpreter->outputs().size() != 3) {
    std::cout << "yolov3 don't support this model!\n";
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    exit(-1);
  }
  int masks[3][3] = {
      {6, 7, 8},
      {3, 4, 5},
      {0, 1, 2},
  };
  float anchors[18] = {10, 13, 16,  30,  33, 23,  30,  61,  62,
                       45, 59, 119, 116, 90, 156, 198, 373, 326};

  for (size_t grid = 0; grid < _interpreter->outputs().size(); grid++) {
    int out = _interpreter->outputs()[grid];
    TfLiteIntArray *out_dims = _interpreter->tensor(out)->dims;
    TfLiteTensor *pOutputTensor = _interpreter->tensor(out);
    int out_batch = out_dims->data[0];
    _out_row = out_dims->data[1];
    _out_colum = out_dims->data[2];
    _out_channel = out_dims->data[3];
    std::cout << "GRID Output Shape:[" << out_batch << "][" << _out_row << "]["
              << _out_colum << "][" << _out_channel << "]\n";

    if (pOutputTensor->type == kTfLiteFloat32) {
      for (size_t i = 0; i < _out_row; i++) {
        for (size_t j = 0; j < _out_colum; j++) {
          for (size_t k = 0; k < _num_anchors; k++) {
            std::vector<float> vtem;
            for (int l = 0; l < _out_channel / _num_anchors; l++) {
              float val_float =
                  pOutputTensor->data
                      .f[i * _out_colum * _out_channel + j * _out_channel +
                         k * _out_channel / _num_anchors + l];
              if (l != 2 && l != 3) {
                val_float =
                    1. / (1. + exp(-val_float)); // logistic (redundancy)
              }
              vtem.push_back(val_float);
            }
            vtem[0] = (j + vtem[0]) / _out_colum;
            vtem[1] = (i + vtem[1]) / _out_row;
            vtem[2] = exp(vtem[2]) * anchors[2 * masks[grid][k]] / _in_width;
            vtem[3] =
                exp(vtem[3]) * anchors[2 * masks[grid][k] + 1] / _in_height;
            v.push_back(vtem);
          }
        }
      }
    } else {
      std::cout << "Unsupported output type!\n";
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;
      exit(-1);
    }
  }
  return v;
}

void YOLOV3::nonMaximumSupprition(std::vector<std::vector<float>> &predV,
                                  std::vector<cv::Rect> &boxes,
                                  std::vector<float> &confidences,
                                  std::vector<int> &classIds,
                                  std::vector<int> &indices)

{
  std::vector<cv::Rect> boxesNMS;
  std::vector<float> scores;
  double confidence;
  cv::Point classId;
  for (int i = 0; i < predV.size(); i++) {
    if (predV[i][4] > _conf_threshold) {
      int left = (predV[i][0] - predV[i][2] / 2) * _img_width;
      int top = (predV[i][1] - predV[i][3] / 2) * _img_height;
      int w = predV[i][2] * _img_width;
      int h = predV[i][3] * _img_height;

      for (int j = 5; j < _out_channel / _num_anchors; j++) {
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
