#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> finalPrices(std::vector<int>& prices) {
        std::vector<int> result(prices.size());
        for (size_t i = 0; i < prices.size(); i++)
        {
            int discount = 0;
            for (size_t j = i + 1; j < prices.size(); j++)
            {
                if(prices[j] <= prices[i]) {
                    discount = prices[j];
                    break;
                }
            }
            result[i] = prices[i] - discount;
        }
        return result;
    }
};

int main() {

    Solution solution;
    std::vector<int> prices1 = {8, 4, 6, 2, 3};
    std::vector<int> prices2 = {1, 2, 3, 4, 5};
    std::vector<int> prices3 = {10, 1, 1, 6};

    std::vector<int> newPrices1 = solution.finalPrices(prices1);
    for(int price1 : newPrices1) {
        std::cout << price1 << " ";
    }
    std::cout << std::endl;

    std::vector<int> newPrices2 = solution.finalPrices(prices2);
    for(int price2 : newPrices2) {
        std::cout << price2 << " ";
    }
    std::cout << std::endl;

    std::vector<int> newPrices3 = solution.finalPrices(prices3);
    for(int price3 : newPrices3) {
        std::cout << price3 << " ";
    }
    std::cout << std::endl;

    return 0;
}