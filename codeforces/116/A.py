n = int(raw_input())
cur = 0
need = 0
for i in xrange(n):
    a = map(int, raw_input().split(' '))
    cur += a[1] - a[0]
    need = max(need, cur)
print need
