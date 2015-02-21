n = int(raw_input())
a = map(int, raw_input().split())
b = [0 for i in xrange(n)]
for i in xrange(n):
    b[a[i] - 1] = i + 1
for i in b:
    print i,
