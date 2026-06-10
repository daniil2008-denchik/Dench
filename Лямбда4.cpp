#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    auto square = [](int x) {
        return x * x;
    };
    
    
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), square);
  
    for (int num : numbers) {
        std::cout << num << " ";
    }
    
    return 0;
}
