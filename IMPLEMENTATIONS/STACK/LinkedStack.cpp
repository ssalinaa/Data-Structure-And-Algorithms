#include <iostream>
#include "LinkedStack.hpp"

int main() {
    try {
        LinkedStack<int> st;

        std::cout << "Pushing elements...\n";
        st.push(10);
        st.push(20);
        st.push(30);

        std::cout << "Top element: " << st.peek() << "\n";  // 30

        std::cout << "Popping...\n";
        st.pop();

        std::cout << "Top after pop: " << st.peek() << "\n"; // 20

        std::cout << "Is empty? " << (st.isEmpty() ? "yes" : "no") << "\n";

        std::cout << "Adding more elements...\n";
        st.push(40);
        st.push(50);

        std::cout << "Current top: " << st.peek() << "\n"; // 50

        std::cout << "Copying stack...\n";
        LinkedStack<int> copy(st);
        std::cout << "Top of copied stack: " << copy.peek() << "\n"; // 50

        std::cout << "Assigning stack...\n";
        LinkedStack<int> assigned;
        assigned = st;
        std::cout << "Top of assigned stack: " << assigned.peek() << "\n"; // 50

        std::cout << "Emptying stack:\n";
        while (!st.isEmpty()) {
            std::cout << "Pop: " << st.peek() << "\n";
            st.pop();
        }

        std::cout << "Stack is empty.\n";

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }

    return 0;
}
