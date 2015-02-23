n = input()
sa = 0
sb = 0
ok = False
for i in xrange(n):
    a, b = map(int, raw_input().split())
    sa += a
    sb += b
    if a % 2 + b % 2 == 1:
        ok = True
if sa % 2 == 0 and sb % 2 == 0:
    print 0
elif sa % 2 == 1 and sb % 2 == 1:
    print 1 if ok else -1
else:
    print -1
