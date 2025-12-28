#include <iostream>
#include "Vector.hpp" 

int main() {

    Vector<int> vec;
    std::cout << "Initial size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";  

    for (int i = 1; i <= 5; i++) {  
        vec.push_back(i * 10);  
    }  

    std::cout << "After push_back, size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";  
    std::cout << "Elements: ";  
    for (size_t i = 0; i < vec.size(); i++) {  
        std::cout << vec[i] << " ";  
    }  
    std::cout << "\n";  

    std::cout << "Front: " << vec.front() << ", Back: " << vec.back() << "\n";  

    vec.pop_back();  
    std::cout << "After pop_back, size: " << vec.size() << ", Back: " << vec.back() << "\n";  

    vec.resize(8);  
    std::cout << "After resize to 8, size: " << vec.size() << ", capacity: " << vec.capacity() << "\n";  
    std::cout << "Elements after resize: ";  
    for (size_t i = 0; i < vec.size(); i++) {  
        std::cout << vec[i] << " ";  
    }  
    std::cout << "\n";  

    vec.resize(3);  
    std::cout << "After resize to 3, size: " << vec.size() << "\n";  
    std::cout << "Elements: ";  
    for (size_t i = 0; i < vec.size(); i++) {  
        std::cout << vec[i] << " ";  
    }  
    std::cout << "\n";  

    vec.reserve(20);  
    std::cout << "After reserve(20), capacity: " << vec.capacity() << "\n";  

    vec.shrink_to_fit();  
    std::cout << "After shrink_to_fit, capacity: " << vec.capacity() << "\n";  

    vec.clear();  
    std::cout << "After clear, size: " << vec.size() << ", empty: " << std::boolalpha << vec.empty() << "\n";  

    return 0;  
}