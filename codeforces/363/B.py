n, k = map(int, raw_input().split())
a = [0] + map(int, raw_input().split())
s = [0]
for i in xrange(1, n+1):
    s.append(s[-1] + a[i])

l = [s[j+k-1] - s[j-1] for j in xrange(1, n+2-k)]
print l.index(min(l)) + 1
