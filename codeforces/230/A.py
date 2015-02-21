s, n = map(int, raw_input().split())
a = []
for i in xrange(n):
    t = map(int, raw_input().split())
    a.append((t[0], t[1]))
a.sort()
for t in a:
    if s <= t[0]:
        print 'NO'
        break
    else:
        s += t[1]
else:
    print 'YES'
