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

TARGET_TOOLCHAIN_PREFIX = aarch64-linux-gnu-

FLATBUFFERS_INC_DIR     = /home/craft/workspace/gem5/tensorflow_src/build/flatbuffers/include/
TFLITE_INC_DIR          = /home/craft/workspace/gem5/tensorflow_src/
OPENCV_INC_DIR          = /home/craft/workspace/gem5/opencv/build/install/include/opencv4/

TFLITE_LIB_DIR          = /home/craft/workspace/gem5/tensorflow_src/build/
TFLITE_FLATBUF_LIB_DIR  = /home/craft/workspace/gem5/tensorflow_src/build/_deps/flatbuffers-build/
TFLITE_RUY_LIB_DIR      = /home/craft/workspace/gem5/tensorflow_src/build/_deps/ruy-build/ruy
OPENCV_LIB_DIR          = /home/craft/workspace/gem5/opencv/build/install/lib/
OPENCV_LIB_3RDPARTY_DIR = /home/craft/workspace/gem5/opencv/build/install/lib/opencv4/3rdparty/

PHONY: all

all: classification segmentation

LIBS  = $(TFLITE_LIB_DIR)/libtensorflow-lite.a
LIBS += $(TFLITE_RUY_LIB_DIR)/libruy_ctx.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_frontend.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_tune.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_context.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_context_get_ctx.a \
	\
	$(TFLITE_RUY_LIB_DIR)/libruy_thread_pool.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_wait.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_allocator.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_system_aligned_alloc.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_cpuinfo.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_blocking_counter.a \
	\
	$(TFLITE_RUY_LIB_DIR)/libruy_apply_multiplier.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_trmul.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_kernel_arm.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_block_map.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_pack_arm.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_prepacked_cache.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_prepare_packed_matrices.a \
	$(TFLITE_RUY_LIB_DIR)/libruy_denormal.a

LIBS += /home/craft/workspace/gem5/tensorflow_src/build/_deps/farmhash-build/libfarmhash.a
LIBS += /home/craft/workspace/gem5/tensorflow_src/build/_deps/flatbuffers-build/libflatbuffers.a
LIBS += /home/craft/workspace/gem5/tensorflow_src/build/_deps/fft2d-build/libfft2d_fftsg.a
LIBS += /home/craft/workspace/gem5/tensorflow_src/build/_deps/fft2d-build/libfft2d_fftsg2d.a
LIBS += /home/craft/workspace/gem5/tensorflow_src/build/_deps/cpuinfo-build/libcpuinfo.a
LIBS += /home/craft/workspace/gem5/tensorflow_src/build/_deps/clog-build/libclog.a

LIBS += $(OPENCV_LIB_DIR)/libopencv_world.a
# -Wl,-rpath-link,$(OPENCV_LIB_DIR)
LIBS += $(OPENCV_LIB_3RDPARTY_DIR)/liblibjpeg-turbo.a $(OPENCV_LIB_3RDPARTY_DIR)/liblibpng.a $(OPENCV_LIB_3RDPARTY_DIR)/libtegra_hal.a $(OPENCV_LIB_3RDPARTY_DIR)/libzlib.a
# -Wl,-rpath-link,$(OPENCV_LIB_3RDPARTY_DIR)
LIBS += -lstdc++ -lpthread -lm -ldl -lrt -static

INCLUDES := -I. -I$(FLATBUFFERS_INC_DIR) -I$(TFLITE_INC_DIR) -I$(OPENCV_INC_DIR)

CCFLAGS = --std=c++11 -O3 -DNDEBUG -fPIC

CXX := ${TARGET_TOOLCHAIN_PREFIX}g++

COMMON_SRC = model_utils.cc utils.cc

classification: classification.cc $(COMMON_SRC)
	$(CXX) classification.cc $(COMMON_SRC) -o tflite_classification $(LDFLAGS) $(LIBS) $(CXXFLAGS) $(CCFLAGS) $(INCLUDES)

segmentation: segmentation.cc $(COMMON_SRC)
	$(CXX) segmentation.cc $(COMMON_SRC) -o tflite_segmentation $(LDFLAGS) $(LIBS) $(CXXFLAGS) $(CCFLAGS) $(INCLUDES)

clean:
	rm -rf classification segmentation
