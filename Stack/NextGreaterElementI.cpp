#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> nextGreaterElement(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::vector<int> ans;

        for(int i = 0; i < nums1.size(); i++) {
            int num = nums1[i];
            int nextGreater = -1;

            for(int j = 0; j < nums2.size(); j++) {
                if(nums2[j] == num) {
                    for(int k = j + 1; k < nums2.size(); k++) {
                        if(nums2[k] > num) {
                            nextGreater = nums2[k];
                            break;
                        }
                    }
                    break;
                }
            }
            ans.push_back(nextGreater);
        }
        return ans;
    }
};

int main() {
    Solution solution;
    std::vector<int> nums1 = {4, 1, 2};
    std::vector<int> nums2 = {1, 3, 4, 2};

    std::vector<int> nums3 = solution.nextGreaterElement(nums1, nums2);
    for (size_t i = 0; i < nums3.size(); i++)
    {
        std::cout << nums3[i] << " ";
    }
    
    return 0;
}