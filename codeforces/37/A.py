n = input()
cnt = [0 for i in xrange(1100)]
for x in map(int, raw_input().split()):
    cnt[x] += 1
print max(cnt), sum([x > 0 for x in cnt])
