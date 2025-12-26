#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    int firstUniqChar(std::string s) {
        std::vector<int> count(26, 0);

        for(char c : s) {
            count[c - 'a']++;
        }

        for(int i = 0; i < s.size(); i++) {
            if(count[s[i] - 'a'] == 1) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    Solution solution;

    std::string s1 = "leetcode";
    std::string s2 = "loveleetcode";
    std::string s3 = "aabb";

    std::cout << solution.firstUniqChar(s1) << std::endl; 
    std::cout << solution.firstUniqChar(s2) << std::endl; 
    std::cout << solution.firstUniqChar(s3) << std::endl; 

    return 0;
}