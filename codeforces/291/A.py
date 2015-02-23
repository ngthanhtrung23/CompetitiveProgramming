cnt = {}
n = input()
a = map(int, raw_input().split())
res = 0
ok = True
for x in a:
    if x == 0:
        continue
    has = cnt.get(x, 0)
    cnt[x] = has + 1
    if has == 1:
        res += 1
    elif has > 1:
        ok = False
if ok:
    print res
else:
    print -1
