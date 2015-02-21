n, k = map(int, raw_input().split())
if k <= n - n/2:
    print 2*k - 1
else:
    print (k - n + n/2) * 2
