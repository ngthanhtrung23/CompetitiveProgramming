m, n = map(int, raw_input().split())
ok = False
for i in xrange(m):
    a = map(int, raw_input().split())
    for j in xrange(n):
        if a[j] == 1:
            if i == 0 or j == 0 or i == m-1 or j == n-1:
                ok = True
print 2 if ok else 4
