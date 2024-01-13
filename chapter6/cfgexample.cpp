#include <iostream>

int main() {
    int x;
    std::cin >> x;
    
    if (x > 0) {
        std::cout << "Positive" << std::endl;
    } else {
        std::cout << "Non-Positive" << std::endl;
    }
    
    return 0;
}
