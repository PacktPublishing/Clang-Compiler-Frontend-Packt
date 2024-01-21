#pragma once

constexpr int fib(int seed, int n) {
  return n <= 2 ? 1
                : fib(seed + (1 << n), n - 1) + fib(seed + (1 << n), n - 2);
}
