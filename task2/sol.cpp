//
// O(nlog n * |s|) времени и O(n) памяти
// Поскольку |s| <= 10 сравнения строк очень быстрые
// 

#include <iostream>
#include <string>
#include <vector>


using namespace std;

bool LexicographicallyLess(const std::string& a, const std::string& b) 
{
    int commonLength = (a.size() < b.size()) ? static_cast<int>(a.size())
                        : static_cast<int>(b.size());

    for (int i = 0; i < commonLength; ++i) 
    {
        if (a[i] != b[i]) return a[i] < b[i];
    }

    return a.size() < b.size();
}

void MergeSort(std::vector<std::string>& a)
{

    int n = static_cast<int>(a.size());
    std::vector<std::string> temporary(n);

    for (int width = 1; width < n; width *= 2)
    {
        for (int left = 0; left < n; left += 2 * width)
        {
            int middle = left + width;
            int right = left + 2 * width;

            if (middle > n) middle = n;
            if (right > n) right = n;

            int first = left;
            int second = middle;
            int position = left;

            while (first < middle && second < right)
            {
                if (LexicographicallyLess(a[second], a[first]))
                    temporary[position++] = a[second++];
                else
                    temporary[position++] = a[first++];
            }

            while (first < middle)
                temporary[position++] = a[first++];

            while (second < right)
                temporary[position++] = a[second++];
        }

        for (int i = 0; i < n; ++i)
        {
            a[i] = temporary[i];
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false); // ускорение ввода, вывода
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::string> strings(n);

    for (int i = 0; i < n; ++i)
        std::cin >> strings[i];

    MergeSort(strings);

    int maximumFrequency = 1;
    int currentFrequency = 1;

    for (int i = 1; i < n; ++i)
    {   
        if (strings[i] == strings[i - 1])
            ++currentFrequency;
        else 
        {
            if (currentFrequency > maximumFrequency)
                maximumFrequency = currentFrequency;
            
            currentFrequency = 1;
        }
    }

    if (currentFrequency > maximumFrequency)
        maximumFrequency = currentFrequency;

    int left = 0;

    while (left < n) 
    {
        int right = left + 1;

        while (right < n && strings[right] == strings[left])
            ++right;

        if (right - left == maximumFrequency)
            std::cout << strings[left] << '\n';

        left = right;
    }

    return 0;
}
