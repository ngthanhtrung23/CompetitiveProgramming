I = lambda: map(int, raw_input().split())
n, s, t = I()
a = I()

for turn in xrange(n+n):
    if s == t:
        print turn
        break
    s = a[s-1]
else:
    print -1
