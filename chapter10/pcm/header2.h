#pragma once

#include "fib_constexpr.h"

namespace header2 {
constexpr int complexity = 27;
constexpr int ga = fib(5, complexity);
}  // namespace header2

int foo2() { return 2; }
