#include <iostream>
#include <stack>

class MyQueue {
public:
    MyQueue() { }

    void push(int x) {
        st1.push(x);
    }

    int pop() {
        if(st2.empty()) {
            while(!st1.empty()) {
                st2.push(st1.top());
                st1.pop();
            }
        }   
        int front = st2.top();
        st2.pop();
        return front;
    }

    int peek() {
        if(st2.empty()) {
            while(!st1.empty()) {
                st2.push(st1.top());
                st1.pop();
            }
        }   
        return st2.top();
    }

    bool empty() {
        return st1.empty() && st2.empty();
    }
private:
    std::stack<int> st1, st2;
};

int main() {
    MyQueue myQueue;
    myQueue.push(1);
    myQueue.push(3);
    myQueue.push(5);

    std::cout << "Top: " << myQueue.peek() << std::endl;
    std::cout << "Pop: " << myQueue.pop() << std::endl;
    std::cout << "Empty: " << std::boolalpha << myQueue.empty() << std::endl;
    std::cout << "Pop: " << myQueue.pop() << std::endl;
    std::cout << "Empty: " << std::boolalpha << myQueue.empty() << std::endl;

    return 0;
}