#include <iostream>
#include <stack>
#include <vector>
#include <string>

class Solution {
public:
    int calPoints(std::vector<std::string>& operations) {
        std::stack<int> st;
        for (size_t i = 0; i < operations.size(); i++)
        {
            if(operations[i] == "C") {
                if(!st.empty()) st.pop();
            } else if(operations[i] == "D") {
                if(!st.empty()) st.push(2 * st.top());
            } else if(operations[i] == "+") {
                if(st.size() >= 2) {
                    int top1 = st.top(); st.pop();
                    int top2 = st.top(); st.push(top1);
                    st.push(top1 + top2);
                } else if(st.size() == 1) {
                    st.push(st.top());
                }
            } else {
                st.push(std::stoi(operations[i]));
            }
        }
        int totalSum = 0;
        while(!st.empty()) {
            totalSum += st.top();
            st.pop();
        }
        return totalSum;
    }
};

int main() {
    Solution solution;
    std::vector<std::string> ops1 = {"5", "2", "C", "D", "+"};
    std::cout << "The total sum of the elements is: " << solution.calPoints(ops1) << std::endl;

    std::vector<std::string> ops2 = {"5", "-2", "4", "C", "D", "9", "+", "+"};
    std::cout << "The total sum of the elements is: " << solution.calPoints(ops2) << std::endl;

    std::vector<std::string> ops3 = {"1", "C"};
    std::cout << "The total sum of the elements is: " << solution.calPoints(ops3) << std::endl;

    return 0;
}