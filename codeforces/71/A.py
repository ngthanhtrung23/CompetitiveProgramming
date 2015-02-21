n = int(raw_input())
for i in xrange(n):
    s = raw_input()
    if len(s) > 10:
        print s[0] + str(len(s) - 2) + s[-1]
    else:
        print s
