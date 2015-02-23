n = input()
a = map(int, raw_input().split())
a.sort()

res = 0
for i in xrange(n):
    res += abs(i+1 - a[i])
print res
