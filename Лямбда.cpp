#include <iostream>

int main() {
    
    auto counter = [count = 0]() mutable {
        return ++count;
    };
    
    
    std::cout << counter() << std::endl;  
    std::cout << counter() << std::endl;  
    std::cout << counter() << std::endl; 
    std::cout << counter() << std::endl;  
    
    return 0;
}
