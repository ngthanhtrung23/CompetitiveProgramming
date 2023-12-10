DIRS = [
    (0, 1),
    (1, 1),
    (1, 0),
    (0, -1),
    (-1, -1),
    (-1, 0),
]

ntests = int(input())
for _ in range(ntests):
    n = int(input())

    print("YES")
    print(7*n)
    for i in range(n):
        i, j = map(int, input().split())
        print(i, j, 3)
        for di, dj in DIRS:
            print(i+di, j+dj, 2)
