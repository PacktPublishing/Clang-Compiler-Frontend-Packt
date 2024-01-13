class TestClass {
public:
  TestClass(){};
  void test_pos(){};

private:
  void private_pos(){};
};

int main() {
  TestClass test;
  test.test_pos();
  return 0;
}
