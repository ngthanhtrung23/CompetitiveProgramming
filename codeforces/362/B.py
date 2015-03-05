I = lambda: map(int, raw_input().split())

n, m = I()
if m > 0:
    a = I()
    a.sort()

if m == 0:
    print 'YES'
elif a[0] == 1 or a[-1] == n:
    print 'NO'
else:
    for i in xrange(m-2):
        if a[i+2] == a[i] + 2:
            print 'NO'
            break
    else:
        print 'YES'
