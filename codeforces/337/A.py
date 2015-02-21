n, m = map(int, raw_input().split())
a = sorted(map(int, raw_input().split()))
res = 1000
for i in xrange(m-n+1):
    res = min(res, a[i+n-1] - a[i])
print res
