#include <iostream>
#include <stack>

int main() {
    std::stack<int> st;
    st.push(1);
    st.push(3);
    st.push(5);
    st.push(7);
    st.push(9);
    std::cout << "Size of the stack: " << st.size() << std::endl;
    std::cout << "Top element is: " << st.top() << std::endl;
    st.pop();
    std::cout << "Top element after pop is: " << st.top() << std::endl;
    st.pop();

    std::stack<int> copy = st;
    std::cout << "Elements present in the stack: " << std::endl;
    while(!copy.empty()) {
        std::cout << copy.top() << " ";
        copy.pop();
    }
   
    return 0;
}