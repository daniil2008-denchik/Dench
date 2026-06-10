#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    
    auto square = [](int x) {
        return x * x;
    };
    
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    
    for (int& num : numbers) {
        num = square(num);
    }
    
    // Вывод результата
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
