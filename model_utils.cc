#include "model_utils.h"

#ifdef TIDL_OFFLOAD
#include "tidl_op.h"
#endif

#include <memory>

#include "tensorflow/lite/builtin_op_data.h"
#include "tensorflow/lite/kernels/register.h"

namespace tflite_example {

std::unique_ptr<tflite::Interpreter> BuildTfliteInterpreter(
    const tflite::FlatBufferModel& model, int num_threads) {
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


std::vector<float> RunInference(tflite::Interpreter* interpreter) {
  std::vector<float> output_data;

  interpreter->Invoke();

  const auto& output_indices = interpreter->outputs();
  const int num_outputs = output_indices.size();
  int out_idx = 0;
  for (int i = 0; i < num_outputs; ++i) {
    const auto* out_tensor = interpreter->tensor(output_indices[i]);
    assert(out_tensor != nullptr);
    if (out_tensor->type == kTfLiteUInt8) {
      const int num_values = out_tensor->bytes;
      output_data.resize(out_idx + num_values);
      const uint8_t* output = interpreter->typed_output_tensor<uint8_t>(i);
      for (int j = 0; j < num_values; ++j) {
        output_data[out_idx++] = (output[j] - out_tensor->params.zero_point) *
                                 out_tensor->params.scale;
      }
    } else if (out_tensor->type == kTfLiteFloat32) {
      const int num_values = out_tensor->bytes / sizeof(float);
      output_data.resize(out_idx + num_values);
      const float* output = interpreter->typed_output_tensor<float>(i);
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

std::array<int, 3> GetInputShape(const tflite::Interpreter& interpreter,
                                 int index) {
  const int tensor_index = interpreter.inputs()[index];
  const TfLiteIntArray* dims = interpreter.tensor(tensor_index)->dims;
  return std::array<int, 3>{dims->data[1], dims->data[2], dims->data[3]};
}

std::array<int, 3> GetOutputShape(const tflite::Interpreter& interpreter,
                                  int index) {
  const int tensor_index = interpreter.outputs()[index];
  const TfLiteIntArray* dims = interpreter.tensor(tensor_index)->dims;
  return std::array<int, 3>{dims->data[1], dims->data[2], dims->data[3]};
}

}  // namespace tflite_example
