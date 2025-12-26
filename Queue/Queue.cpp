#include <iostream>
#include <queue>
 
int main() {
    std::queue<int> q;
    q.push(1);
    q.push(3);
    q.push(5);
    q.push(7);
    q.push(9);
    std::cout << "Size of the queue: " << q.size() << std::endl;
    std::cout << "Front element: " << q.front() << std::endl;
    std::cout << "Back element: " << q.back() << std::endl;
    std::cout << "Removing element from the front: " << std::endl;
    q.pop();
    std::cout << "Front element after pop: " << q.front() << std::endl;
    
    return 0;
}