#!/usr/bin/env bash
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

set -e

export TARGET_TOOLCHAIN_PREFIX=riscv64-unknown-linux-gnu-

export TFLITE_BUILD_DIR=/home/craft/workspace/gem5/tensorflow_src/buildrv64

export OPENCV_SRC_DIR=/home/craft/workspace/gem5/opencv
export OPENCV_BUILD_DIR=/home/craft/workspace/gem5/opencv/buildrv64

export JDSK_DL_ACC=yes

make
