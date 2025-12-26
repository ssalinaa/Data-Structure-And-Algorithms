#include <iostream>
#include <string>
#include <stack>

class Solution {
public:
    std::string removeOuterParentheses(std::string s) {
        std::string newstr = "";
        int count = 0;

        for(char c : s) {
            if(c == '(') {
                if(count > 0) newstr += c;
                count++; 
            } else {
                count--;
                if(count > 0) newstr += c;
            }
        }
        return newstr;
    }
};

int main() {
    Solution solution;
    std::string str1 = "(()())(())";
    std::string str2 = "(()())(())(()(()))";
    std::string str3 = "()()";

    std::cout << "String after removing parentheses: " << solution.removeOuterParentheses(str1) << std::endl;
    std::cout << "String after removing parentheses: " << solution.removeOuterParentheses(str2) << std::endl;
    std::cout << "String after removing parentheses: " << solution.removeOuterParentheses(str3) << std::endl;

    return 0;
}