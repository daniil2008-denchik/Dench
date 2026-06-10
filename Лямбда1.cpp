#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<std::string> words = {"apple", "cat", "dog", "banana", "car", "zebra", "a", "ant"};
    
    
    std::sort(words.begin(), words.end(),
        [](const std::string& a, const std::string& b) {
            if (a.length() != b.length()) {
                return a.length() < b.length();  
            }
            return a < b;  
        }
    );
    
    
    for (const auto& word : words) {
        std::cout << word << std::endl;
    }
    
    return 0;
}
