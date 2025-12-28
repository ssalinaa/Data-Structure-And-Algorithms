#include <iostream>
#include <string>
#include "CircularQueue.hpp"   // ако е в отделен хедър, иначе махни този ред

using namespace std;

int main() {
    CircularQueue<int> q;

    cout << "Enqueue 1, 2, 3, 4:\n";
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);

    cout << "Front element: " << q.peek() << endl;

    cout << "Dequeue two elements:\n";
    q.dequeue();
    q.dequeue();

    cout << "Front element: " << q.peek() << endl;

    cout << "Enqueue 5, 6:\n";
    q.enqueue(5);
    q.enqueue(6);

    cout << "Front element: " << q.peek() << endl;

    cout << "Dequeuing everything:\n";
    while (!q.isEmpty()) {
        cout << q.peek() << " ";
        q.dequeue();
    }

    cout << "\nQueue is now empty." << endl;

    return 0;
}
