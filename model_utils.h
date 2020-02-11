#ifndef MODEL_UTILS_H_
#define MODEL_UTILS_H_

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/model.h"

namespace tflite_example {

// Builds tflite Interpreter.
std::unique_ptr<tflite::Interpreter> BuildTfliteInterpreter(
    const tflite::FlatBufferModel& model, int num_threads);

// Runs inference using given `interpreter`
std::vector<float> RunInference(tflite::Interpreter* interpreter);

// Returns input tensor shape in the form {height, width, channels}.
std::array<int, 3> GetInputShape(const tflite::Interpreter& interpreter,
                                 int index);

// Returns output tensor shape in the form {height, width, channels}.
std::array<int, 3> GetOutputShape(const tflite::Interpreter& interpreter,
                                  int index);

}  // namespace tflite_example
#endif  // MODEL_UTILS_H_
