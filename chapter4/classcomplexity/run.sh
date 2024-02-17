#!/bin/bash
../../../llvm-project/install/bin/clang -Xclang -load -Xclang ./build/libClassComplexityChecker.so -Xclang -plugin -Xclang class-complexity-checker -fsyntax-only simple_test.cpp
