#include <iostream>
#include "ArrayStack.hpp"

int main() {
    ArrayStack<int> arrayStack;
    arrayStack.push(1);
    arrayStack.push(3);
    arrayStack.push(5);
    std::cout << "Stack's size: " << arrayStack.size() << std::endl;
    std::cout << "Stack's peek: " << arrayStack.peek() << std::endl;
    arrayStack.pop();
    std::cout << "Stack's peek: " << arrayStack.peek() << std::endl;
    std::cout << "Stack's size: " << arrayStack.size() << std::endl;

    ArrayStack<int> newArrayStack = arrayStack;
    std::cout << "New stack's size: " << newArrayStack.size() << std::endl;
    std::cout << "New stack's peek: " << newArrayStack.peek() << std::endl;

    std::cout << "Elements present in the stack: " << std::endl;
    while(!newArrayStack.isEmpty()) {
        std::cout << newArrayStack.peek() << " ";
        newArrayStack.pop();
    }

    return 0;
}