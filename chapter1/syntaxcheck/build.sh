#!/bin/sh
./cleanup.sh
export LLVM_HOME=`pwd`/../../../../llvm-project/install
mkdir build
cd build
cmake -G Ninja ..
ninja
