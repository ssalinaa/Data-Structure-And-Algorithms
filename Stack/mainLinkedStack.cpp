#include <iostream>
#include "LinkedStack.hpp"

int main() {
    LinkedStack<int> list;
    list.push(15);
    list.push(20);
    list.push(25);
    std::cout << "List's top element: " << list.peek() << std::endl;
    list.pop();
    std::cout << "Is list empty?: " << std::boolalpha << list.isEmpty() << std::endl;
    std::cout << "List's top element: " << list.peek() << std::endl;
    list.pop();
    list.push(30);
    LinkedStack<int> newList = list;
    std::cout << "New list's top element: " << list.peek() << std::endl;

    return 0;
}