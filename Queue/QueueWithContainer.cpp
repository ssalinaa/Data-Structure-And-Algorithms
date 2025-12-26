#include <iostream>
#include "QueueWithContainer.hpp"

int main() {
    Queue<int> q;
    q.push(1);
    q.push(3);
    q.push(5);
    q.push(7);
    q.push(9);
    std::cout << "The size of the queue is: " << q.size() << std::endl;
    std::cout << "Front element of the queue is: " << q.front() << std::endl;
    q.pop();
    std::cout << "The size of the queue is: " << q.size() << std::endl;
    std::cout << "Front element of the queue is: " << q.front() << std::endl;
    std::cout << "Back element of the queue is: " << q.back() << std::endl;

    return 0;
}