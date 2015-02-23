x, y, a, b = map(int, raw_input().split())
res = []
for i in xrange(a, x+1):
    for j in xrange(b, min(y, i-1)+1):
        res.append((i, j))
print len(res)
res.sort()
for p in res:
    print p[0], p[1]
