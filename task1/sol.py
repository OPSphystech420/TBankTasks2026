# время O(nlogn)
# память O(n)

n = int(input())
a = list(map(int, input().split()))


a.sort()

if a[0] + a[1] == a[2] and all(x == a[2] for x in a[2:]):
    print("YES")
else:
    print("NO")
