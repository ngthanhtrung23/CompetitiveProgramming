k = input()
l = input()

for i in xrange(1, 40):
    if k ** i == l:
        print 'YES'
        print i-1
        break
else:
    print 'NO'
