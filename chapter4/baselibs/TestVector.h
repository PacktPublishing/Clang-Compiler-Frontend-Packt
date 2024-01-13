#pragma once

#include "llvm/ADT/SmallVector.h"
#include "CommonHeaders.h"

void testSmallVector() {
  llvm::SmallVector<int, 10> SmallVector;
  for (int i = 0; i < 10; i++) {
    SmallVector.push_back(i);
  }
  SmallVector.push_back(10);
  for (int i = 0; i < SmallVector.size(); ++i) {
    llvm::outs() << llvm::formatv("SmallVector[{0}]: {1}\n", i, SmallVector[i]);
  }
}
