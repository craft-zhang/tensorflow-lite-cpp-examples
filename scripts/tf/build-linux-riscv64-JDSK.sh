#!/usr/bin/env bash
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
# tf v2.9.1 tested

set -e

mkdir -p build_tflite

CMAKE_ARGS=()

# CMake-level configuration
CMAKE_ARGS+=("-DCMAKE_MAKE_PROGRAM=make")
CMAKE_ARGS+=("-DCMAKE_CROSSCOMPILING=1")
CMAKE_ARGS+=("-DCMAKE_TOOLCHAIN_FILE=$(pwd)/scripts/tf/cmake/riscv64.JDSK.toolchain.cmake")
CMAKE_ARGS+=("-DCMAKE_BUILD_TYPE=RelWithDebInfo")

# Cross-compilation options for Google Benchmark

CMAKE_ARGS+=("-DHAVE_POSIX_REGEX=0")
CMAKE_ARGS+=("-DHAVE_STEADY_CLOCK=0")
CMAKE_ARGS+=("-DHAVE_STD_REGEX=0")

# install
CMAKE_ARGS+=("-DCMAKE_INSTALL_PREFIX=$(pwd)/tflite")
CMAKE_ARGS+=("-DTFLITE_ENABLE_INSTALL=ON")
CMAKE_ARGS+=("ABSL_ENABLE_INSTALL=ON")
CMAKE_ARGS+=("-DCMAKE_FIND_PACKAGE_PREFER_CONFIG=ON")
CMAKE_ARGS+=("-Dabsl_DIR=$(pwd)/tflite/lib/cmake/absl")
CMAKE_ARGS+=("-DEigen3_DIR=$(pwd)/tflite/share/eigen3/cmake")
CMAKE_ARGS+=("-DFlatbuffers_DIR=$(pwd)/tflite/lib/cmake/flatbuffers")
CMAKE_ARGS+=("-DNEON_2_SSE_DIR=$(pwd)/tflite/lib/cmake/NEON_2_SSE")
CMAKE_ARGS+=("-Dcpuinfo_DIR=$(pwd)/tflite/share/cpuinfo")
CMAKE_ARGS+=("-Druy_DIR=$(pwd)/tflite/lib/cmake/ruy")

# xnnpack
CMAKE_ARGS+=("-DTFLITE_ENABLE_XNNPACK=ON")

# Use-specified CMake arguments go last to allow overridding defaults
CMAKE_ARGS+=($@)

pushd build_tflite

# change to your path
cmake ../../tensorflow/tensorflow/lite "${CMAKE_ARGS[@]}"

cmake --build .

popd

# cp 