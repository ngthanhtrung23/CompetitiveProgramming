import sys

def get(a, b):
    if (a == 0 or b == 0):
        return 0
    if (a == b):
        return 1
    if (a > b):
        return get(b, a)

    res = b // a
    b = b % a
    return get(b, a) + res

ntest = int(input())
for i in range(0, ntest):
    tmp = list(map(int, input().split()))
    a = tmp[0]
    b = tmp[1]
    print(get(a, b))
