n = input()
bottom = 7 - input()
tmp = raw_input()

for i in xrange(1, n):
    x, y = map(int, raw_input().split())
    x = min(x, 7-x)
    y = min(y, 7-y)
    z = 6-x-y
    if z != bottom and z != 7-bottom:
        print 'NO'
        break
else:
    print 'YES'
