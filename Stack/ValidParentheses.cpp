#include <iostream>
#include <string>
#include <stack>

class Solution {
public:

    bool isOpeningBracket(char c) {
        return c == '{' || c == '(' || c == '[';
    }

    bool isValid(std::string s) {
        std::stack<int> st;
        for(char c : s) {
            if(isOpeningBracket(c)) {
                st.push(c);
            } else {
                if(st.empty() ||
                    (c == ')' && st.top() != '(') || 
                    (c == '}' && st.top() != '{') ||
                    (c == ']' && st.top() != '[')) {
                        return false;
                }
                st.pop();
            }
        }
        return st.empty();
    }
};

int main() {
    Solution solution;
    std::string str1 = "()";
    std::string str2 = "()[]{}";
    std::string str3 = "(]";
    std::string str4 = "([])";
    std::string str5 = "([)]";

    std::cout << "Is valid string? : " << std::boolalpha << solution.isValid(str1) << std::endl;
    std::cout << "Is valid string? : " << std::boolalpha << solution.isValid(str2) << std::endl;
    std::cout << "Is valid string? : " << std::boolalpha << solution.isValid(str3) << std::endl;
    std::cout << "Is valid string? : " << std::boolalpha << solution.isValid(str4) << std::endl;
    std::cout << "Is valid string? : " << std::boolalpha << solution.isValid(str5) << std::endl;
   
    return 0;
}