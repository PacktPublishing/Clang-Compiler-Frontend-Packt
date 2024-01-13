#include <iostream>
#include <vector>

int main() {
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end();
       ++it) {
    std::cout << *it << std::endl;
  }
  return 0;
}
