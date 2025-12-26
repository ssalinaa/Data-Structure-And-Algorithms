#include <iostream>
#include "StackWithContainer.hpp"

int main() {
    Stack <int> st;
    st.push(1);
    st.push(3);
    st.push(5);
    
    std::cout << "Top element is: " << st.top() << std::endl;
    st.pop();
    std::cout << "Top element is: " << st.top() << std::endl;

    return 0;
}