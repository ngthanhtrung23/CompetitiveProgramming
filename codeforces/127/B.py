n = input()
a = map(int, raw_input().split())
cnt = [0] * 111
for x in a:
    cnt[x] += 1

sides = 0
for x in xrange(101):
    sides += cnt[x] / 2
print sides / 2
