s = raw_input()
l = len(s)


def good(a):
    if a == '0':
        return True
    if a[0] == '0':
        return False
    if len(a) > 7:
        return False
    return 0 <= int(a) <= 10 ** 6

res = -1
for i in xrange(1, l):
    for j in xrange(i+1, l):
        a = s[:i]
        b = s[i:j]
        c = s[j:]
        if good(a) and good(b) and good(c):
            res = max(res, int(a) + int(b) + int(c))
print res
