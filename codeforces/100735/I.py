a = int(raw_input())
b = int(raw_input())
c = int(raw_input())


def check(a, b, c):
    x = [a, b, c]
    for i in xrange(3):
        for j in xrange(3):
            if x[i] + x[j] in x:
                return True
    return False


if check(a, b, c):
    print "YES"
else:
    print "NO"
