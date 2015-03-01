from collections import defaultdict
values = map(int, raw_input().split())
a = ' ' + raw_input()
s = [0] * len(a)

for i in xrange(1, len(a)):
    s[i] = s[i-1] + values[ord(a[i]) - ord('a')]

cnt = defaultdict(int)
res = 0

for i in xrange(1, len(a)):
    res += cnt[(s[i-1], a[i])]
    cnt[(s[i], a[i])] += 1
print res
