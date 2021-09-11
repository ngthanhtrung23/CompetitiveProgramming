s1 = raw_input()
s2 = raw_input()

for l in xrange(min(len(s2), len(s1)), -1, -1):
    if s2[:l] == s1[-l:]:
        print len(s1 + s2[l:])
        break
    if l == 0:
        print len(s1 + s2)
