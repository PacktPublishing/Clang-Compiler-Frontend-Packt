#!/bin/sh
./cleanup.sh
export LLVM_HOME=`pwd`/../../../../llvm-project-16.x/install
mkdir build
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
ninja
