n, m = map(int, raw_input().split())
cur = 1
res = 0
for x in map(int, raw_input().split()):
    if cur <= x:
        res += x - cur
    else:
        res += n - cur + x
    cur = x
print res
