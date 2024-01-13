class TestClass {
public:
  int foo(){return 0};
};

int main() {
  TestClass test;
  int foo = test.foo();
  return foo;
}
