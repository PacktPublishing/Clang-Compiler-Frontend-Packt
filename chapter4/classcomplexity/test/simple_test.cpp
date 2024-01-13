// RUN: %clang-binary -fplugin=%path-to-plugin -fsyntax-only %s 2>&1 | %file-check-binary %s

class Simple {
public:
  void func1() {}
  void func2() {}
};

// CHECK: :[[@LINE+1]]:{{[0-9]+}}: warning: class Complex is too complex: method count = 6
class Complex {
public:
  void func1() {}
  void func2() {}
  void func3() {}
  void func4() {}
  void func5() {}
  void func6() {}
};
