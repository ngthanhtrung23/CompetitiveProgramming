m = input()
c = map(int, raw_input().split())
x, y = map(int, raw_input().split())
s = sum(c)
cur = 0
for i in xrange(m):
    cur += c[i]
    if x <= cur <= y and x <= s-cur <= y:
        print i+2
        break
else:
    print 0
