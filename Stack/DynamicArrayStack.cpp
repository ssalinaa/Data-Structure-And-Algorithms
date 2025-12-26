#include <iostream>
#include <vector>

int main() {
    std::vector<int> stack;
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);
    stack.push_back(4);
    stack.push_back(5);

    std::cout << "Stack's size: " << stack.size() << std::endl;
    std::cout << "Stack's top element: " << stack.back() << std::endl;
    stack.pop_back();
    std::cout << "Stack's top element: " << stack.back() << std::endl;

    std::cout << "Elements present in the stack: " << std::endl;
    while(!stack.empty()) {
        std::cout << stack.back() << " ";
        stack.pop_back();
    }

    return 0;
}