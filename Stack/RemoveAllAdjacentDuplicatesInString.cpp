#include <iostream>
#include <string>
#include <stack>

class Solution {
public:
    std::string removeDuplicates(std::string s) {
        std::stack<char> st;
        for(char c: s) {
            if(!st.empty() && c == st.top()) {
                st.pop();
            } else {
                st.push(c);
            }
        }

        std::string result;
        while (!st.empty()) {
            result = st.top() + result;
            st.pop();
        }

        return result;
    }
};

int main() {

    Solution solution;
    std::string str1 = "abbaca";
    std::string str2 = "azxxzy";

    std::cout << "String after removing duplicates: " << solution.removeDuplicates(str1) << std::endl;
    std::cout << "String after removing duplicates: " << solution.removeDuplicates(str2) << std::endl;

    return 0;
}