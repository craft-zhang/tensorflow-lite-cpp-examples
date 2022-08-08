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

#ifndef MODEL_UTILS_H_
#define MODEL_UTILS_H_

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/model.h"

namespace tflite_example
{

    // Builds tflite Interpreter.
    std::unique_ptr<tflite::Interpreter> BuildTfliteInterpreter(
        const tflite::FlatBufferModel &model, int num_threads);

    // Runs inference using given `interpreter`
    std::vector<float> RunInference(tflite::Interpreter *interpreter, double &inference_time_ms);

    // Returns input tensor shape in the form {height, width, channels}.
    std::array<int, 3> GetInputShape(const tflite::Interpreter &interpreter,
                                     int index);

    // Returns output tensor shape in the form {height, width, channels}.
    std::array<int, 3> GetOutputShape(const tflite::Interpreter &interpreter,
                                      int index);

} // namespace tflite_example
#endif // MODEL_UTILS_H_
