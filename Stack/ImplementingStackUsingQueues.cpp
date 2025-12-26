#include <iostream>
#include <queue>

class MyStack {
public:
    MyStack() { }

    void push(int x) {
        q2.push(x);
        while(!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }
    int pop() {
        if(q1.empty()) return -1;
        int topElement = q1.front();
        q1.pop();
        return topElement;
    }
    int top() {
        if(q1.empty()) return -1;
        return q1.front();
    }
    bool empty() {
        return q1.empty();
    }
public:
    std::queue<int> q1, q2;
};

int main() {
    MyStack myStack;
    myStack.push(1);
    myStack.push(2);
    
    std::cout << "Top: " << myStack.top() << std::endl;
    std::cout << "Pop: " << myStack.pop() << std::endl;
    std::cout << "Empty: " << std::boolalpha << myStack.empty() << std::endl;
    std::cout << "Pop: " << myStack.pop() << std::endl;
    std::cout << "Empty: " << std::boolalpha << myStack.empty() << std::endl;

    return 0;
}