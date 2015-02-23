n = input()
res = -1
cur = 0
for i in xrange(n):
    h = input()
    res += abs(h - cur)
    cur = h
print res + n + n
