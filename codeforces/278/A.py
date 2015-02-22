n = input()
a = [0]
a.extend(map(int, raw_input().split()))
s = [0 for i in xrange(n+1)]
for i in xrange(1, n+1):
    s[i] = s[i-1] + a[i]
fr, to = map(int, raw_input().split())
if fr > to:
    fr, to = to, fr

x = s[to-1] - s[fr-1]
y = s[fr-1] + s[n] - s[to-1]
print min(x, y)
