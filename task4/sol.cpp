//
// время O(n)
// память O(1)
//

#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false); // ускорение ввода, вывода
    std::cin.tie(nullptr);

    int n;
    std::int64_t k;  // n_max = 5*10^5
    
    std::cin >> n >> k;

    int left = 1;
    int right = n;
    bool first = true;

    for (int remaining = n; remaining >= 1; --remaining)
    {
        int value;

        if (k >= remaining - 1)
        {
            value = right;
            --right;
            k -= remaining - 1;
        }
        else
        {
            value = left;
            ++left;
        }

        if (!first) std::cout << ' ';

        std::cout << value;
        first = false;
    }

    std::cout << '\n';
    return 0;
}
