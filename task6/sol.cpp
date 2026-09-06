//
// время O(n * 2^n)
// память O(n * 2^n) для таблицы призов и O(2^n) для динамики
//
// Пусть dp[i] максимальная сумма призов уже выбывших игроков
// внутри текущей части сетки при условии что вышел игрок i.
// Приз самого i пока не учитываем, потому что он продолжает турнир
//

#include <iostream>
#include <vector>

using namespace std;

using int64 = int64_t;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int playerCount = 1 << n;

    // prize[i][wins] - приз iго игрока за wins
    // при wins = 0 приз равен нулю
    std::vector<std::vector<int64>> prize(
        playerCount,
        std::vector<int64>(n + 1, 0)
    );

    for (int player = 0; player < playerCount; ++player)
        for (int wins = 1; wins <= n; ++wins)
            std::cin >> prize[player][wins];

    std::vector<int64> dp(playerCount, 0);
    std::vector<int64> nextDp(playerCount, 0);

    for (int round = 1; round <= n; ++round)
    {
        int halfSize = 1 << (round - 1);
        int blockSize = halfSize * 2;

        for (
            int blockStart = 0;
            blockStart < playerCount;
            blockStart += blockSize
        ) {
            int middle = blockStart + halfSize;
            int blockEnd = blockStart + blockSize;

            int64 bestLeft = -1;
            int64 bestRight = -1;

            // лучший возможный победитель левой половины
            // если затем он проиграет в текущем раунде
            for (int player = blockStart; player < middle; ++player)
            {
                int64 value =
                    dp[player] + prize[player][round - 1];

                if (value > bestLeft) bestLeft = value;
            }

            // аналогично для правой половины
            for (int player = middle; player < blockEnd; ++player)
            {
                int64 value =
                    dp[player] + prize[player][round - 1];

                if (value > bestRight) bestRight = value;
            }

            // Если текущий блок выигрывает игрок слева оптимально выбираем проигравшего справа
            for (int player = blockStart; player < middle; ++player)
                nextDp[player] = dp[player] + bestRight;

            // Если текущий блок выигрывает игрок справа
            for (int player = middle; player < blockEnd; ++player)
                nextDp[player] = dp[player] + bestLeft;
        }

        dp.swap(nextDp);
    }

    int64 answer = 0;

    // Последний оставшийся игрок одержал n побед и приз
    for (int player = 0; player < playerCount; ++player)
    {
        int64 total = dp[player] + prize[player][n];

        if (total > answer) answer = total;
    }

    std::cout << answer << '\n';
    return 0;
}
