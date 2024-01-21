#pragma once

#include "fib_constexpr.h"

namespace header3 {
constexpr int complexity = 27;
constexpr int ga = fib(7, complexity);
}  // namespace header3

int foo3() { return 3; }
