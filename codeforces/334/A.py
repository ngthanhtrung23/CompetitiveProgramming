n = input()
a = [[0 for i in xrange(n)] for j in xrange(n)]
for x in xrange(n*n):
    if (x / n) % 2 == 0:
        a[x % n][x / n] = str(x + 1)
    else:
        a[n - 1 - x % n][x / n] = str(x + 1)
for i in xrange(n):
    print ' '.join(a[i])
