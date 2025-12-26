#include <iostream>
#include "CircularQueue.hpp"

int main()
{
	CircularQueue<int> q;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	std::cout << "Front element is: " << q.peek() << std::endl;
	q.dequeue();
	std::cout << "Front element is: " << q.peek() << std::endl;
	q.dequeue();
	std::cout << "Front element is: " << q.peek() << std::endl;
	q.dequeue();
	std::cout << "Front element is: " << q.peek() << std::endl;
	q.dequeue();
	std::cout << "Front element is: " << q.peek() << std::endl;
	q.dequeue();

	std::cout << "Is queue empty?: " << std::boolalpha << q.isEmpty() << std::endl;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	CircularQueue<int> q2(q);
	std::cout << "Front element is: " << q.peek() << std::endl;
	q.dequeue();
	std::cout << "Front element is: " << q.peek() << std::endl;
	q.dequeue();
	std::cout << "Front element is: " << q.peek() << std::endl;
	q.dequeue();
	std::cout << "Front element is: " << q.peek() << std::endl;
	q.dequeue();
	std::cout << "Front element is: " << q.peek() << std::endl;
	q.dequeue();

    return 0;
}