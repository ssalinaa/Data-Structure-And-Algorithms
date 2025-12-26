#include <iostream>
#include <string>
#include <stack>

class Solution {
public:
    bool backspaceCompare(std::string s, std::string t) {
        std::stack<char> s1;
        std::stack<char> t1;

        for(char c1 : s) {
            if(c1 != '#') {
                s1.push(c1);
            } else if(!s1.empty()) {
                s1.pop();
            }
        }

        for(char c2 : t) {
            if(c2 != '#') {
                t1.push(c2);
            } else if(!t1.empty()) {
                t1.pop();
            }
        }

        while(!s1.empty() && !t1.empty()) {
            if(s1.top() != t1.top()) {
                return false;
            }
            s1.pop();
            t1.pop();
        }
        return s1.empty() && t1.empty();
    }
};

int main() {
    Solution solution;
    std::string s1 = "ab#c";
    std::string t1 = "ad#c";
    std::cout << "Are strings equal? " << std::boolalpha << solution.backspaceCompare(s1, t1) << std::endl;

    std::string s2 = "ab##";
    std::string t2 = "c#d#";
    std::cout << "Are strings equal? " << std::boolalpha << solution.backspaceCompare(s2, t2) << std::endl;

    std::string s3 = "a#c";
    std::string t3 = "b";
    std::cout << "Are strings equal? " << std::boolalpha << solution.backspaceCompare(s3, t3) << std::endl;

    return 0;
}