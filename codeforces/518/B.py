s = raw_input()
t = raw_input()

cnt = [0] * 300
used = [0] * len(s)
for c in t:
    cnt[ord(c)] += 1

c1 = 0
c2 = 0

for i in xrange(len(s)):
    c = s[i]
    if cnt[ord(c)] > 0:
        c1 += 1
        cnt[ord(c)] -= 1
        used[i] = 1

for i in xrange(len(s)):
    c = s[i]
    if used[i] == 0 and cnt[ord(c) ^ 32] > 0:
        c2 += 1
        cnt[ord(c) ^ 32] -= 1

print c1, c2
