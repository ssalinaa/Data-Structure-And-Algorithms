#include <iostream>
#include "LinkedQueue.hpp"

int main() {
    try {
        LinkedQueue<int> q;

        std::cout << "Enqueuing elements...\n";
        q.enqueue(10);
        q.enqueue(20);
        q.enqueue(30);

        std::cout << "Front element: " << q.peek() << "\n"; // 10

        std::cout << "Dequeuing...\n";
        q.dequeue();

        std::cout << "Front after dequeue: " << q.peek() << "\n"; // 20

        std::cout << "Is empty? " << (q.isEmpty() ? "yes" : "no") << "\n";

        std::cout << "Adding more elements...\n";
        q.enqueue(40);
        q.enqueue(50);

        std::cout << "Current front: " << q.peek() << "\n"; // 20

        std::cout << "Copying queue...\n";
        LinkedQueue<int> copy(q);
        std::cout << "Front of copied queue: " << copy.peek() << "\n"; // 20

        std::cout << "Assigning queue...\n";
        LinkedQueue<int> assigned;
        assigned = q;
        std::cout << "Front of assigned queue: " << assigned.peek() << "\n"; // 20

        std::cout << "Emptying queue:\n";
        while (!q.isEmpty()) {
            std::cout << "Dequeue: " << q.peek() << "\n";
            q.dequeue();
        }

        std::cout << "Queue is empty.\n";

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }

    return 0;
}