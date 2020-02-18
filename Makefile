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

PHONY: all

all: classification segmentation
LIBS = -lstdc++ -ltensorflow-lite -lpthread -lm -lz -ldl -lrt

LIBS += -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_imgproc -lopencv_core

INCLUDES := -I.

CXXFLAGS += --std=c++11

CXX := $(CC_PREFIX)${TARGET_TOOLCHAIN_PREFIX}g++

COMMON_SRC = model_utils.cc utils.cc

ifeq ($(TIDL_ACC), yes)
  COMMON_SRC += tidl_op.cc
endif

classification: classification.cc $(COMMON_SRC)
	$(CXX) classification.cc $(COMMON_SRC) -o tflite_classification $(LDFLAGS) $(LIBS) $(CXXFLAGS) $(INCLUDES)

segmentation: segmentation.cc $(COMMON_SRC)
	$(CXX) segmentation.cc $(COMMON_SRC) -o tflite_segmentation $(LDFLAGS) $(LIBS) $(CXXFLAGS) $(INCLUDES)

clean:
	rm -rf classification segmentation
