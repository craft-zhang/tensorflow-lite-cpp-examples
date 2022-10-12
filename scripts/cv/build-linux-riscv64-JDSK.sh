#!/usr/bin/env bash
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
# OpenCV v4.6.x tested

set -e

mkdir -p build_cv

CMAKE_ARGS=()

# CMake-level configuration
CMAKE_ARGS+=("-DCMAKE_MAKE_PROGRAM=make")
CMAKE_ARGS+=("-DCMAKE_CROSSCOMPILING=1")
CMAKE_ARGS+=("-DCMAKE_TOOLCHAIN_FILE=$(pwd)/scripts/tf/cmake/riscv64.JDSK.toolchain.cmake")
CMAKE_ARGS+=("-DCMAKE_BUILD_TYPE=RelWithDebInfo")
CMAKE_ARGS+=("-DBUILD_SHARED_LIBS=OFF")
CMAKE_ARGS+=("-DOPENCL_FOUND=OFF")
CMAKE_ARGS+=("-DBUILD_PERF_TESTS=OFF")
CMAKE_ARGS+=("-DBUILD_TESTS=OFF")
CMAKE_ARGS+=("-DBUILD_opencv_apps=OFF")
CMAKE_ARGS+=("-DBUILD_opencv_calib3d=OFF")
CMAKE_ARGS+=("-DBUILD_opencv_gapi=OFF")

# install
# CMAKE_INSTALL_PREFIX

# Use-specified CMake arguments go last to allow overridding defaults
CMAKE_ARGS+=($@)

pushd build_cv

# change to your path
ccmake ../../../gem5/opencv/ "${CMAKE_ARGS[@]}"

cmake --build .

popd

# cp 