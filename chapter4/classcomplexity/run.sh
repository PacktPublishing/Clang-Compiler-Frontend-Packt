#!/bin/bash
../../../llvm-project/install/bin/clang -fsyntax-only -fplugin=./build/libclasschecker.so ./test/simple_test.cpp
../../../llvm-project/install/bin/clang -fsyntax-only -fplugin-arg-classchecker-threshold=2 -fplugin=./build/libclasschecker.so test.cpp
