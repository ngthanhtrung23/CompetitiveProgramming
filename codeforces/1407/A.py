ntest = int(input())

for test in range(ntest):
    n = int(input())
    a = list(map(int, input().split()))
    res = []
    for i in range(0, n-3, 4):
        if sum(a[i:i+4]) >= 3:
            res.extend([1, 1])
        else:
            res.extend([0, 0])
    if n % 4 == 2:
        if sum(a[-2:]) == 2:
            res.extend([1, 1])
        else:
            res.extend([0])
    print(len(res))
    print(' '.join(map(str, res)))
