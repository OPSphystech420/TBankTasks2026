//сортировка O(nlog n)
//один подсчет O(n)
//двоичный поиск O(nlog R), R - диапазон произведений
//память O(n)

#include <iostream>
#include <vector>

using namespace std;

using int128 = __int128;
// произведения считаем в __int128 чтобы избежать переполнения

using int64 = int64_t;

void MergeSort(std::vector<int64>& values)
{
    int n = static_cast<int>(values.size());
    std::vector<int64> buffer(n);

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
                if (values[first] <= values[second])
                    buffer[position++] = values[first++];
                else
                    buffer[position++] = values[second++];
            }

            while (first < middle)
                buffer[position++] = values[first++];

            while (second < right)
                buffer[position++] = values[second++];
            
        }

        values.swap(buffer);
    }
}

// все элементы values положительны и отсортированы
int64 CountPositivePairs(const std::vector<int128>& values, int128 limit)
{
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;
    int64 count = 0;

    while (left < right)
    {
        if (values[left] * values[right] <= limit)
        {
            // c values[left] подходят все элементы
            // от left+1 до right
            count += right - left;
            ++left;
        }
        else --right;
    }

    return count;
}

int64 CountProductsNotGreater(
    int128 limit,
    const std::vector<int128>& negative,
    const std::vector<int128>& positive,
    const std::vector<int128>& negativeAbsolute,
    int64 zeroCount,
    int n
) {
    int64 negativeCount = static_cast<int64>(negative.size());
    int64 positiveCount = static_cast<int64>(positive.size());

    if (limit < 0)
    {
        // Подходить могут только отрицательные произведения
        int64 count = 0;
        int positiveIndex = 0;

        // negative идет от наиболее отрицательного
        // к числам близким к нулю
        for (int128 negativeValue : negative)
        {
            while (
                positiveIndex < positiveCount
                && negativeValue * positive[positiveIndex] > limit
            ) { ++positiveIndex; }

            count += positiveCount - positiveIndex;
        }

        return count;
    }

    // Все отрицательные произведения подходят
    int64 count = negativeCount * positiveCount;

    // Все пары содержащие хотя бы один ноль
    count += zeroCount * (n - zeroCount);
    count += zeroCount * (zeroCount - 1) / 2;

    // Положительные
    count += CountPositivePairs(positive, limit);
    count += CountPositivePairs(negativeAbsolute, limit);

    return count;
}

void PrintInt128(int128 value)
{
    if (value == 0)
    {
        std::cout << "0\n";
        return;
    }

    if (value < 0)
    {
        std::cout << '-';
        value = -value;
    }

    char digits[50];
    int length = 0;

    while (value > 0)
    {
        digits[length++] =
            static_cast<char>( '0' + static_cast<int>(value % 10));
        value /= 10;
    }

    while (length > 0)
        std::cout << digits[--length];

    std::cout << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false); // ускорение ввода, вывода
    std::cin.tie(nullptr);

    int n;
    int64 k;
    std::cin >> n >> k;

    std::vector<int64> a(n);

    for (int i = 0; i < n; ++i)
        std::cin >> a[i];

    MergeSort(a);

    std::vector<int128> negative;
    std::vector<int128> positive;
    std::vector<int128> negativeAbsolute;
    int64 zeroCount = 0;

    for (int64 value : a)
    {
        if (value < 0)
            negative.push_back(static_cast<int128>(value));
        else if (value > 0)
            positive.push_back(static_cast<int128>(value));
        else
            ++zeroCount;
    }

    // модули отрицательных чисел должны идти по возрастанию
    for (int i = static_cast<int>(negative.size()) - 1; i >= 0; --i) {
        negativeAbsolute.push_back(-negative[i]);
    }

    // минимальное и максимальное произведения находятся
    // среди этих трех пар уже отсортированного массива
    int128 product1 = static_cast<int128>(a[0]) * a[1];
    int128 product2 = static_cast<int128>(a[0]) * a[n - 1];
    int128 product3 = static_cast<int128>(a[n - 2]) * a[n - 1];

    int128 lower = product1;
    int128 upper = product1;

    if (product2 < lower)
        lower = product2;
    
    if (product3 < lower)
        lower = product3;
    
    if (product2 > upper)
        upper = product2;

    if (product3 > upper)
        upper = product3;
    

    while (lower < upper)
    {
        int128 middle = lower + (upper - lower)  / 2;

        int64 count = CountProductsNotGreater(
            middle,
            negative,
            positive,
            negativeAbsolute,
            zeroCount,
            n
        );

        if (count >= k) upper = middle;
        else lower = middle + 1;
    }

    PrintInt128(lower);
    return 0;
}
