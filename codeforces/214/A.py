n, m = map(int, raw_input().split())
res = 0
for a in xrange(50):
    for b in xrange(50):
        if a*a + b == n and a + b*b == m:
            res += 1
print res
