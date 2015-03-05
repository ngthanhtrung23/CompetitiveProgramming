from collections import defaultdict

cnt = defaultdict(int)
s = raw_input()
for c in s:
    cnt[c] += 1

g = sum([cnt[x] % 2 for x in cnt])
if g <= 1:
    print "First"
elif g % 2 == 0:
    print "Second"
else:
    print "First"
