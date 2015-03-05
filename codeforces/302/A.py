from collections import defaultdict

I = lambda: map(int, raw_input().split())
cnt = defaultdict(int)
n, m = I()
a = I()
for x in a:
    cnt[x] += 1

for i in xrange(m):
    l, r = I()
    sz = r - l + 1
    if sz % 2 == 1:
        print 0
    elif cnt[1] >= sz / 2 and cnt[-1] >= sz/2:
        print 1
    else:
        print 0
