/*
 * Copyright 2019 Google LLC
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

#include "model_utils.h"
#include <sys/time.h>

#ifdef TIDL_OFFLOAD
#include "tidl_op.h"
#endif

#include <memory>

#include "tensorflow/lite/builtin_op_data.h"
#include "tensorflow/lite/kernels/register.h"

namespace tflite_example {

std::unique_ptr<tflite::Interpreter>
BuildTfliteInterpreter(const tflite::FlatBufferModel &model, int num_threads) {
  tflite::ops::builtin::BuiltinOpResolver resolver;
#ifdef TIDL_OFFLOAD
  resolver.AddCustom(tidl::kTidlSubgraphOp, tidl::RegisterTidlSubgraphOp());
#endif

  std::unique_ptr<tflite::Interpreter> interpreter;
  if (tflite::InterpreterBuilder(model, resolver)(&interpreter) != kTfLiteOk) {
    std::cerr << "Failed to build interpreter." << std::endl;
  }
  interpreter->SetNumThreads(num_threads);
  if (interpreter->AllocateTensors() != kTfLiteOk) {
    std::cerr << "Failed to allocate tensors." << std::endl;
  }
  return interpreter;
}

/*
 * Get time in us
 */
double get_us(struct timeval t) { return (t.tv_sec * 1000000 + t.tv_usec); }

std::vector<float> RunInference(tflite::Interpreter *interpreter,
                                double &inference_time_ms) {
  std::vector<float> output_data;

  struct timeval start_time, stop_time;
  gettimeofday(&start_time, nullptr);

  // Running the inference
  interpreter->Invoke();

  gettimeofday(&stop_time, nullptr);
  inference_time_ms = (get_us(stop_time) - get_us(start_time)) / 1000;

  const auto &output_indices = interpreter->outputs();
  const int num_outputs = output_indices.size();
  int out_idx = 0;
  for (int i = 0; i < num_outputs; ++i) {
    const auto *out_tensor = interpreter->tensor(output_indices[i]);
    assert(out_tensor != nullptr);
    if (out_tensor->type == kTfLiteUInt8) {
      const int num_values = out_tensor->bytes;
      output_data.resize(out_idx + num_values);
      const uint8_t *output = interpreter->typed_output_tensor<uint8_t>(i);
      for (int j = 0; j < num_values; ++j) {
        output_data[out_idx++] = (output[j] - out_tensor->params.zero_point) *
                                 out_tensor->params.scale;
      }
    } else if (out_tensor->type == kTfLiteFloat32) {
      const int num_values = out_tensor->bytes / sizeof(float);
      output_data.resize(out_idx + num_values);
      const float *output = interpreter->typed_output_tensor<float>(i);
      for (int j = 0; j < num_values; ++j) {
        output_data[out_idx++] = output[j];
      }
    } else {
      std::cerr << "Tensor " << out_tensor->name
                << " has unsupported output type: " << out_tensor->type
                << std::endl;
    }
  }
  return output_data;
}

std::array<int, 3> GetInputShape(const tflite::Interpreter &interpreter,
                                 int index) {
  const int tensor_index = interpreter.inputs()[index];
  const TfLiteIntArray *dims = interpreter.tensor(tensor_index)->dims;
  return std::array<int, 3>{dims->data[1], dims->data[2], dims->data[3]};
}

std::array<int, 3> GetOutputShape(const tflite::Interpreter &interpreter,
                                  int index) {
  const int tensor_index = interpreter.outputs()[index];
  const TfLiteIntArray *dims = interpreter.tensor(tensor_index)->dims;
  return std::array<int, 3>{dims->data[1], dims->data[2], dims->data[3]};
}

} // namespace tflite_example
