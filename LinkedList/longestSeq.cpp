#include <iostream>
#include <vector>

template <typename It, typename Pred>
It longestSeq(It first, It last, Pred p)
{
    It best_start = last;    
    std::size_t best_len = 0;

    It cur_start = last;
    std::size_t cur_len = 0;

    for (It it = first; it != last; ++it)
    {
        if (p(*it))
        {
            if (cur_len == 0)
                cur_start = it;    

            ++cur_len;
        }
        else
        {
            if (cur_len > best_len)
            {
                best_len = cur_len;
                best_start = cur_start;
            }
            cur_len = 0;
        }
    }

    if (cur_len > best_len)
    {
        best_len = cur_len;
        best_start = cur_start;
    }

    return best_start;
}

int main()
{
    std::vector<int> v{1, 2, 4, 6, 7, 8, 10, 12, 14, 1, 3, 5};

    auto it = longestSeq(v.begin(), v.end(), 
                         [](int x){ return x % 2 == 0; });

    if (it != v.end())
        std::cout << "Най-дълга поредица започва при стойност: " << *it << "\n";
    else
        std::cout << "Няма елементи, удовлетворяващи предиката.\n";
}