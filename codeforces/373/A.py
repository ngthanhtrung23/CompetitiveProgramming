can = input() * 2
cnt = [0] * 1111
for i in xrange(4):
    a = raw_input()
    for c in a:
        cnt[ord(c)] += 1
cnt[ord('.')] = 0
print 'YES' if max(cnt) <= can else 'NO'
