k = input()
a = map(int, raw_input().split())
a.sort()
a.reverse()

if (k > sum(a)):
    print -1
else:
    res = 0
    while k > 0:
        k -= a[res]
        res += 1
    print res
