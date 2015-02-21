n = input()
a = map(int, raw_input().split())
res = -1
for i in xrange(n):
    for j in xrange(i, n):
        for k in xrange(i, j+1):
            a[k] = 1 - a[k]
        res = max(res, sum(a))
        for k in xrange(i, j+1):
            a[k] = 1 - a[k]
print res
