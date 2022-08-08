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

#include "tensorflow/lite/kernels/internal/tensor.h"
#include "tensorflow/lite/kernels/kernel_util.h"

#include "tidl_op.h"

#include "subgraph_runtime.h"

#include <iostream>
using namespace std;

namespace tidl
{
  namespace tidl_subgraph_op
  {

    using tflite::GetInput;
    using tflite::GetOutput;
    using tflite::GetTensorData;
    using tflite::NumDimensions;
    using tflite::NumInputs;
    using tflite::NumOutputs;

    struct OpData
    {
      int dummy; // Use OpData to pass data from Init() to Prepare()/Eval()
    };

    void *Init(TfLiteContext *context, const char *buffer, size_t length)
    {
      auto *op_data = new OpData;
      const uint8_t *buffer_t = reinterpret_cast<const uint8_t *>(buffer);

      // A single subgraph with subgraph index of 0
      TidlInitSubgraph(1, 0);

      return op_data;
    }

    void Free(TfLiteContext *context, void *buffer)
    {
      TidlFreeSubgraph(1, 0);
      delete reinterpret_cast<OpData *>(buffer);
    }

    TfLiteStatus Prepare(TfLiteContext *context, TfLiteNode *node)
    {
      // Populate the data initialized during Init() call
      OpData *data = reinterpret_cast<OpData *>(node->user_data);

      // Get the input and output tensors
      TfLiteTensor *output = GetOutput(context, node, 0);
      const TfLiteTensor *input = GetInput(context, node, 0);

      // Allocate buffer for the output
      int num_dims = NumDimensions(output);
      TfLiteIntArray *output_size = TfLiteIntArrayCreate(num_dims);
      for (int i = 0; i < num_dims; ++i)
      {
        output_size->data[i] = output->dims->data[i];
      }

      return context->ResizeTensor(context, output, output_size);
    }

    TfLiteStatus Eval(TfLiteContext *context, TfLiteNode *node)
    {
      // Populate the data initialized during Init() call
      OpData *data = reinterpret_cast<OpData *>(node->user_data);

      // Get the input and output tensors
      TfLiteTensor *output = GetOutput(context, node, 0);
      const TfLiteTensor *input = GetInput(context, node, 0);

      float *input_data = input->data.f;
      float *output_data = output->data.f;

#ifdef DEBUG
      FILE *filePtr;
      filePtr = fopen("floatArray_tidl_input", "w");

      std::cout << "input dimension: ";
      int num_dims = NumDimensions(input);
      int input_size = 1;
      for (int i = 0; i < num_dims; i++)
      {
        input_size = input_size * input->dims->data[i];
        std::cout << input->dims->data[i] << "x";
      }

      std::cout << std::endl;

      for (int i = 0; i < input_size; i++)
      {
        fprintf(filePtr, "%.10g\t", input_data[i]);
        if (i % 9 == 8)
          fprintf(filePtr, "\n");
      }
#endif

      // A single subgraph with subgraph index of 0,
      // batch size 1, sinlge input tensor, and single output tensor
      TidlRunSubgraph(1, 0, 1, 1, 1, &input_data, &output_data);

#ifdef DEBUG
      FILE *filePtrOut;
      filePtrOut = fopen("floatArray_tidl_output", "w");

      std::cout << "output dimension: ";
      num_dims = NumDimensions(output);
      int output_size = 1;
      for (int i = 0; i < num_dims; i++)
      {
        output_size = output_size * output->dims->data[i];
        std::cout << output->dims->data[i] << "x";
      }

      std::cout << std::endl;

      for (int i = 0; i < output_size; i++)
      {
        fprintf(filePtrOut, "%.10g\t", output_data[i]);
        if (i % 9 == 8)
          fprintf(filePtrOut, "\n");
      }
#endif

      return kTfLiteOk;
    }

  } // namespace tidl_subgraph_op

  TfLiteRegistration *RegisterTidlSubgraphOp()
  {
    static TfLiteRegistration r = {
        tidl_subgraph_op::Init, tidl_subgraph_op::Free,
        tidl_subgraph_op::Prepare, tidl_subgraph_op::Eval};
    return &r;
  }

} // namespace tidl
