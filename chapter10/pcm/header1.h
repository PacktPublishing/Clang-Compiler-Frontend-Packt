#pragma once

#include "fib_constexpr.h"

namespace header1 {
constexpr int complexity = 27;
constexpr int ga = fib(3, complexity);
}  // namespace header1

int foo1() { return 1; }
