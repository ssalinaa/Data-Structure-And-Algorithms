#include <iostream>
#include <string>
#include <stack>

class Solution {
public:
    std::string makeGood(std::string s) {
        std::stack<char> st;
        
        for(char c : s) {
            if(!st.empty() && std::tolower(st.top()) == std::tolower(c) && st.top() != c) {
                st.pop();
            } else {
                st.push(c);
            }
        }

        std::string result = "";
        while(!st.empty()) {
            result = st.top() + result;
            st.pop();
        }
        return result;
    }
};

int main() {

    Solution solution;
    std::string str1 = "leEeetcode";
    std::string str2 = "abBAcC";
    std::string str3 = "s";

    std::cout << "The new string is: " << solution.makeGood(str1) << std::endl;
    std::cout << "The new string is: " << solution.makeGood(str2) << std::endl;
    std::cout << "The new string is: " << solution.makeGood(str3) << std::endl;

    return 0;
}