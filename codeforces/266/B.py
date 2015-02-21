t = map(int, raw_input().split())
s = raw_input()
for i in xrange(t[1]):
    s = s.replace('BG', 'GB')
print s
