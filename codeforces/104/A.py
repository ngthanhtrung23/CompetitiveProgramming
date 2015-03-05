from collections import defaultdict

cnt = defaultdict(int)
for i in xrange(1, 14):
    if i == 1:
        cnt[1] += 4
        cnt[11] += 4
    elif i > 10:
        cnt[10] += 4
    else:
        cnt[i] += 4

n = input()
cnt[10] -= 1

print cnt[n - 10]
