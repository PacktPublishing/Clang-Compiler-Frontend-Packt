class TestClass {
public:
  TestClass(){};
  void pos() { this->private_pos(); };

private:
  void private_pos(){};
};

class NotTestClass {
public:
  NotTestClass(){};
  void pos(){};
};

int main() {
  TestClass test;
  test.pos();

  NotTestClass not_test;
  not_test.pos();

  return 0;
}
