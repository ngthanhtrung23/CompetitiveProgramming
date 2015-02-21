import fractions

a = map(int, raw_input().split(' '))
while True:
    x = fractions.gcd(a[0], a[2])
    if a[2] < x:
        print 1
        break
    else:
        a[2] -= x
    y = fractions.gcd(a[1], a[2])
    if a[2] < y:
        print 0
        break
    else:
        a[2] -= y
