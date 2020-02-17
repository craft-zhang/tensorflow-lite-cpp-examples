#ifndef TIDL_OP_H_
#define TIDL_OP_H_

#include "tensorflow/lite/c/c_api_internal.h"

namespace tidl {

  static const char kTidlSubgraphOp[] = "tidl-am5-custom-op";

  TfLiteRegistration* RegisterTidlSubgraphOp();

}  // namespace tidl

#endif
