#include <iostream>
#include "ArrayStack.hpp"

int main() {

    ArrayStack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);

    std::cout << "Top: " << st.peek() << std::endl;
    std::cout << "Size: " << st.size() << std::endl;
    
    st.pop();
    std::cout << "After pop, top: " << st.peek() << std::endl;

    st.push(40);
    std::cout << "After push, top: " << st.peek() << std::endl;

    while(!st.isEmpty()) {
        std::cout << "Popping: " << st.peek() << std::endl;
        st.pop();
    }
    
    return 0;
}