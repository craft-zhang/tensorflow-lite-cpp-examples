# Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

SYSROOT_INCDIR      ?= /usr/include
FLATBUFFERS_INC_DIR ?= $(SYSROOT_INCDIR)
TFLITE_INC_DIR      ?= $(SYSROOT_INCDIR)
OPENCV_INC_DIR      ?= $(SYSROOT_INCDIR)

SYSROOT_LIBDIR      ?= /usr/lib
TFLITE_LIB_DIR      ?= $(SYSROOT_LIBDIR)
OPENCV_LIB_DIR      ?= $(SYSROOT_LIBDIR)

PHONY: all

all: classification segmentation

LIBS = -L $(TFLITE_LIB_DIR) -ltensorflow-lite
LIBS += -L $(OPENCV_LIB_DIR) -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_imgproc -lopencv_core -Wl,-rpath-link,$(OPENCV_LIB_DIR)
LIBS += -lstdc++ -lpthread -lm -lz -ldl -lrt

INCLUDES := -I. -I$(FLATBUFFERS_INC_DIR) -I$(TFLITE_INC_DIR) -I$(OPENCV_INC_DIR)

CCFLAGS = --std=c++11 -O3 -DNDEBUG -fPIC

CXX := $(CC_PREFIX)${TARGET_TOOLCHAIN_PREFIX}g++

COMMON_SRC = model_utils.cc utils.cc

TIDL_ACC ?= no
ifeq ($(TIDL_ACC), yes)
  COMMON_SRC += tidl_op.cc
  CCFLAGS += -DTIDL_OFFLOAD

  TIDL_API_DIR     ?= /usr/share/ti/tidl
  TIDL_API_INC_DIR ?= $(TIDL_API_DIR)/tidl_api/inc
  INCLUDES += -I$(TIDL_API_INC_DIR)

  TIDL_API_LIB_DIR ?= $(SYSROOT_LIBDIR)
  LIBS += -L $(TIDL_API_LIB_DIR) -ltidl_api
endif

classification: classification.cc $(COMMON_SRC)
	$(CXX) classification.cc $(COMMON_SRC) -o tflite_classification $(LDFLAGS) $(LIBS) $(CXXFLAGS) $(CCFLAGS) $(INCLUDES)

segmentation: segmentation.cc $(COMMON_SRC)
	$(CXX) segmentation.cc $(COMMON_SRC) -o tflite_segmentation $(LDFLAGS) $(LIBS) $(CXXFLAGS) $(CCFLAGS) $(INCLUDES)

clean:
	rm -rf classification segmentation
