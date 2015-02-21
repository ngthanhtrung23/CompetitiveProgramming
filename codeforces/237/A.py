n = input()
cnt = [0 for i in xrange(25 * 60)]
for i in xrange(n):
    h, m = map(int, raw_input().split())
    cnt[h * 60 + m] += 1
print max(cnt)
