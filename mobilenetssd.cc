#include "mobilenetssd.h"

// void MobileNetSSD::preprocess(cv::Mat &image) {
//   if (image.data) {
//     // std::cout << "Cvt Color Space to RGB\n";
//     // cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
//     std::cout << "Resize to fit input Shape\n";
//     cv::resize(image, image, cv::Size(_in_height, _in_width));
//     // cv::imwrite("image.jpg", image);
//     // image.convertTo(image, CV_32FC3);
//   } else {
//     std::cout << "input image is empty!\n";
//     std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//     exit(-1);
//   }
// }

void MobileNetSSD::run(cv::Mat &frame, Prediction &out_pred) {
  do {
    if (!frame.data) {
      std::cout << "input image is empty!\n";
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;
      exit(-1);
    }

    _img_height = frame.rows;
    _img_width = frame.cols;

    preprocess(frame);
    if (_in_type == kTfLiteFloat32) {
      fill(_input_f32, frame);
    } else if (_in_type == kTfLiteUInt8) {
      fill(_input_u8, frame);
    }

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
      TfLiteType out_type =
          _interpreter->tensor(_interpreter->outputs()[i])->type;
      int out_batch = out_dims->data[0];
      int out_row = out_dims->data[1];
      int out_colum = out_dims->data[2];
      int out_channel = out_dims->data[3];
      std::cout << "YOLO Model Output Shape:[" << out_batch << "][" << out_row
                << "][" << out_colum << "][" << out_channel << "] "
                << " type: [" << out_type << "]\n";
    }

    size_t N = _interpreter->tensor(_interpreter->outputs()[5])->data.f[0];
    float *detection_boxes =
        _interpreter->tensor(_interpreter->outputs()[1])->data.f;
    float *detection_classes =
        _interpreter->tensor(_interpreter->outputs()[2])->data.f;
    float *detection_scores =
        _interpreter->tensor(_interpreter->outputs()[4])->data.f;

    for (int i = 0; i < N; i++) {
      if (detection_scores[i] > _conf_threshold) {
        out_pred.scores.push_back(detection_scores[i]);
        out_pred.labels.push_back(floor(detection_classes[i] + 0.5f));
        cv::Rect bbox;
        bbox.y = detection_boxes[4 * i] * _img_height;
        bbox.x = detection_boxes[4 * i + 1] * _img_width;
        bbox.height =
            (detection_boxes[4 * i + 2] - detection_boxes[4 * i]) * _img_height;
        bbox.width = (detection_boxes[4 * i + 3] - detection_boxes[4 * i + 1]) *
                     _img_width;
        out_pred.boxes.push_back(bbox);
      }
    }
  } while (0);
};