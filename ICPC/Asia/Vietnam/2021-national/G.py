#!/usr/bin/env python3

n, k = map(int, input().split())
a = list(map(int, input().split()))

if n == 0:
    print('0 0')
else:
    a = [0 if x == 1 else x for x in a]

    a = sorted(a)
    s = [0]
    for x in a:
        s.append(s[-1] + x)

    print(s[k], s[n] - s[n-k])
