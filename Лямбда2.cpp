#include <iostream>
#include <string>

int main() {
    
    auto getMax = [](const auto& a, const auto& b) -> const auto& {
        return a > b ? a : b;
    };
    
    
    int x = 10, y = 20;
    std::cout << "Max int: " << getMax(x, y) << std::endl;
    
   
    double d1 = 3.14, d2 = 2.71;
    std::cout << "Max double: " << getMax(d1, d2) << std::endl;
    
    
    std::string s1 = "apple", s2 = "banana";
    std::cout << "Max string: " << getMax(s1, s2) << std::endl;
    
    
    return 0;
}
