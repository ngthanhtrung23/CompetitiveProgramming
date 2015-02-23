import math

n = input()
r = map(int, raw_input().split())
r.sort()
r.reverse()


def area(r):
    return r*r*math.pi

res = 0
for i in xrange(n):
    if i % 2 == 0:
        res += area(r[i])
    else:
        res -= area(r[i])
print res
