import math


def dist(P, Q):
    return math.sqrt((P[0]-Q[0])**2 + (P[1]-Q[1])**2)

I = lambda: map(int, raw_input().split())
n, k = I()
a = []
for i in xrange(n):
    x, y = I()
    a.append((x, y))


res = 0.0
for i in xrange(n-1):
    res += dist(a[i], a[i+1])
print res*k/50.0
