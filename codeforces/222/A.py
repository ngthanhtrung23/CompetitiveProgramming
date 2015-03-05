I = lambda: map(int, raw_input().split())
n, k = I()
a = I()

if min(a) == max(a):
    print 0
else:
    x = n-1
    while a[x] == a[n-1]:
        x -= 1
    if x + 1 > k - 1:
        print -1
    else:
        print x+1
