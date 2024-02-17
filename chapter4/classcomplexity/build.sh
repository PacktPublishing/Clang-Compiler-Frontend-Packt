#!/bin/sh
./cleanup.sh
export LLVM_SRC=`pwd`/../../../llvm-project
export LLVM_HOME=$LLVM_SRC/install
export LLVM_BUILD=$LLVM_SRC/build

mkdir build
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
ninja classchecker
ninja check-classchecker
