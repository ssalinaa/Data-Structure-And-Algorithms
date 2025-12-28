#include <iostream>
#include "Set.hpp"

int main() {
    Set s;

    int array[] = { 5,1,3,2,6,8,7,9,4,0 };
    for (size_t i = 0; i < 10; i++)
    {
        s.insert(array[i]);
    }

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << s[i] << std::endl;
    }
    
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << s.getRank(i) << std::endl;
    }

    for(auto it = s.begin(); it != s.end(); ++it) {
        std::cout << (*it);
    }

    return 0;
}