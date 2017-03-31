s = raw_input()
a = eval(s)

def digit(c):
    print '>'
    for i in xrange(48 + c):
        print '+'
    print '.'


if a >= 100:
    digit(a / 100)
    digit((a % 100) / 10)
    digit(a % 10)
elif a >= 10:
    digit(a / 10)
    digit(a % 10)
else:
    digit(a)
