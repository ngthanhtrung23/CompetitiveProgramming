n, m = map(int, raw_input().split())
a = map(int, raw_input().split())

occurs = [-1] * 100111
f = [0] * 100111
for i in xrange(n-1, -1, -1):
    f[i] = f[i+1]
    if occurs[a[i]] < 0:
        f[i] += 1
    occurs[a[i]] = i

for i in xrange(m):
    x = input() - 1
    print f[x]
