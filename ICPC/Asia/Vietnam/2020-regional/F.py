n = int(raw_input())
s = ''
for i in xrange(n):
    s += raw_input()

res = 0
for i in xrange(n-1):
    if s[i] == s[i+1]:
        res += 1
print res

