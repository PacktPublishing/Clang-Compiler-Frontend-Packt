#pragma once

template <int seed, int n>
struct Fib {
  enum {
    value = static_cast<int>(Fib<seed, n - 1>::value) +
            static_cast<int>(Fib<seed + (1 << n), n - 2>::value),
  };
};

template <int seed>
struct Fib<seed, 2> {
  enum { value = 1 };
};

template <int seed>
struct Fib<seed, 1> {
  enum { value = 1 };
};
