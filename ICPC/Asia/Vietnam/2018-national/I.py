# https://vietnam-national18.kattis.com/problems/iwannabe
n, k = map(int, raw_input().split())
a = [[0, 0, 0]] * n

for i in xrange(n):
    a[i] = (map(int, raw_input().split()), i)

x = sorted(a, key=lambda x: -x[0][0])
y = sorted(a, key=lambda x: -x[0][1])
z = sorted(a, key=lambda x: -x[0][2])

all = set()
for i in xrange(k):
    all.add(x[i][1])
    all.add(y[i][1])
    all.add(z[i][1])
print len(all)
