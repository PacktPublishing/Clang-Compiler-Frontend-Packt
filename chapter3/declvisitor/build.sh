#!/bin/sh
./cleanup.sh
export LLVM_HOME=`pwd`/../../../llvm-project/install
mkdir build
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
ninja
ninja preprocess
