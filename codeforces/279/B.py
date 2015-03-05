I = lambda: map(int, raw_input().split())

n, t = I()
a = I()

fr = 0
cur = 0
res = 0
for to in xrange(n):
    cur += a[to]
    while cur > t:
        cur -= a[fr]
        fr += 1
    res = max(res, to - fr + 1)
print res
