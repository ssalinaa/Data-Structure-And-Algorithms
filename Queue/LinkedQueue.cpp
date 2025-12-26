#include <iostream>
#include "LinkedQueue.hpp"

int main() {
    LinkedQueue<int> q;
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    q.enqueue(7);
    q.enqueue(9);
    std::cout << "Is queue empty?: " << std::boolalpha << q.isEmpty() << std::endl;
    std::cout << "Front element of the queue is: " << q.peek() << std::endl;
    q.dequeue();
    std::cout << "Front element of the queue is: " << q.peek() << std::endl;
    q.dequeue();
    std::cout << "Front element of the queue is: " << q.peek() << std::endl;
    q.dequeue();
    std::cout << "Front element of the queue is: " << q.peek() << std::endl;
    
    return 0;
}