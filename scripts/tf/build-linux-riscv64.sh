#!/usr/bin/env bash
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
# tf v2.11.1 tested

set -e
rm -rf build_tflite_2_11_x
mkdir -p build_tflite_2_11_x

CMAKE_ARGS=()

# CMake-level configuration
CMAKE_ARGS+=("-DCMAKE_MAKE_PROGRAM=make")
CMAKE_ARGS+=("-DCMAKE_TOOLCHAIN_FILE=$(pwd)/scripts/tf/cmake/riscv64.JDSK.toolchain.cmake")
CMAKE_ARGS+=("-DCMAKE_BUILD_TYPE=RelWithDebInfo")

# Cross-compilation options for Google Benchmark
CMAKE_ARGS+=("-DHAVE_POSIX_REGEX=0")
CMAKE_ARGS+=("-DHAVE_STEADY_CLOCK=0")
CMAKE_ARGS+=("-DHAVE_STD_REGEX=0")

# xnnpack
CMAKE_ARGS+=("-DTFLITE_ENABLE_XNNPACK=ON")

# flatbuffer
# 防止交叉编译出的elf直接运行报错
CMAKE_ARGS+=("-DFLATBUFFERS_BUILD_FLATC=OFF")
# 最好有预装
CMAKE_ARGS+=("-DFLATBUFFERS_FLATC_EXECUTABLE=flatc")

# Use-specified CMake arguments go last to allow overridding defaults
CMAKE_ARGS+=($@)

pushd build_tflite_2_11_x

# 需要手动修改tensorflow的地址
cmake ../../tensorflow/tensorflow/lite "${CMAKE_ARGS[@]}"
make -j4

popd
