from collections import defaultdict

n = input()
a = map(int, raw_input().split())
cnt = defaultdict(int)

for x in a:
    cnt[x] += 1
res = 0
for i in xrange(11):
    if i == 0:
        res += cnt[i] * (cnt[i] - 1) / 2
    else:
        res += cnt[i] * cnt[-i]
print res
