#include <iostream>
#include <vector>

int main() {
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  for (int & number : numbers) {
    std::cout << number << std::endl;
  }
  return 0;
}
