n = input()
a = map(int, raw_input().split())
best = a[0]
worst = a[0]
res = 0
for i in xrange(1, n):
    if a[i] > best:
        best = a[i]
        res += 1
    if a[i] < worst:
        worst = a[i]
        res += 1
print res
