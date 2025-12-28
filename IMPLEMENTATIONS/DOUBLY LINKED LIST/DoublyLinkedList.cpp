#include <iostream>
#include "DoublyLinkedList.hpp"

int main() {
    
    DoublyLinkedList<int> list;
    std::cout << "Initial list: size = " << list.getSize()
              << ", empty = " << std::boolalpha << list.isEmpty() << "\n\n";
    
    list.pushBack(10);
    list.pushFront(20);
    list.pushBack(5);
    list.pushFront(30);
    
    std::cout << "After pushFront/pushBack:\n";
    std::cout << "Front = " << list.front() << ", Back = " << list.back() 
              << ", Size = " << list.getSize() << "\n\n";
    
    list.popFront();
    std::cout << "After popFront(): Front = " << list.front() 
              << ", Size = " << list.getSize() << "\n";
    
    list.popBack();
    std::cout << "After popBack(): Back = " << list.back() 
              << ", Size = " << list.getSize() << "\n\n";
    
    DoublyLinkedList<int> copyList(list);
    std::cout << "Copy of list (copyList): Front = " << copyList.front() 
              << ", Back = " << copyList.back() << ", Size = " << copyList.getSize() << "\n";
    
    DoublyLinkedList<int> movedList(std::move(copyList));
    std::cout << "Move-constructed list (movedList): Front = " << movedList.front() 
              << ", Back = " << movedList.back() << ", Size = " << movedList.getSize() << "\n";
    std::cout << "(copyList should now be empty: Size = " << copyList.getSize() << ")\n\n";
    
    movedList.clear();
    std::cout << "After clear(): Size = " << movedList.getSize() 
              << ", Empty = " << std::boolalpha << movedList.isEmpty() << "\n";
    
    return 0;
}
