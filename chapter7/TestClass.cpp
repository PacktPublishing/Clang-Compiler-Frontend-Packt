class TestClass {
public:
  TestClass(){};
  void pos(){};

private:
  void private_pos(){};
};

int main() {
  TestClass test;
  test.pos();
  return 0;
}
