# время O(t)
# память O(n)

def solve():
    n, t = map(int, input().split())
    cells = list(map(int, input().split()))

    rows = [0] * n
    columns = [0] * n

    main_diagonal = 0
    secondary_diagonal = 0

    round_number = 0

    for cell in cells:
        round_number += 1

        # Переходим от нумерации 1..n^2 к нумерации 0..n^2-1
        cell -= 1

        row = cell // n
        column = cell % n

        rows[row] += 1
        columns[column] += 1

        if row == column:
            main_diagonal += 1

        if row + column == n - 1:
            secondary_diagonal += 1

        if (
            rows[row] == n
            or columns[column] == n
            or main_diagonal == n
            or secondary_diagonal == n
        ):
            print(round_number)
            return

    print(-1)


solve()
