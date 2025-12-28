#include <iostream>
#include "SinglyLinkedList.hpp"

int main() {

    SinglyLinkedList<int> list;
    std::cout << "Initial: size = " << list.getSize() 
              << ", empty = " << std::boolalpha << list.isEmpty() << "\n\n";

    list.pushFront(10);
    list.pushFront(20);
    list.pushBack(5);

    std::cout << "After pushing 20, 10 (front) and 5 (back):\n";
    list.print(); 
    std::cout << "\nsize = " << list.getSize() << "\n";
    std::cout << "front = " << list.front() 
              << ", back = " << list.back() << "\n\n";

    list.popFront();
    std::cout << "After popFront():\n";
    list.print();
    std::cout << "\nfront = " << list.front() 
              << ", size = " << list.getSize() << "\n\n";

    SinglyLinkedList<int> copyList(list);
    std::cout << "Copy of list:\n";
    copyList.print();
    std::cout << "\n\n";

    SinglyLinkedList<int> movedList(std::move(copyList));
    std::cout << "Move constructed list:\n";
    movedList.print();
    std::cout << "\n(copyList should now be empty)\n\n";

    SinglyLinkedList<int> a;
    SinglyLinkedList<int> b;

    a.pushBack(1);
    a.pushBack(2);

    b.pushBack(3);
    b.pushBack(4);

    SinglyLinkedList<int> c = concat(a, b);

    std::cout << "Concatenated list (c = a + b):\n";
    c.print();
    std::cout << "\nsize = " << c.getSize() << "\n";

    std::cout << "\n(a and b should now be empty)\n";

    return 0;
}