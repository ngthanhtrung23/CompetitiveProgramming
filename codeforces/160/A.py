n = raw_input()
a = sorted(map(int, raw_input().split(' ')))
a.reverse()
cur = 0
suma = sum(a)
for i in xrange(len(a)):
    cur += a[i]
    if cur > suma - cur:
        print i+1
        break
