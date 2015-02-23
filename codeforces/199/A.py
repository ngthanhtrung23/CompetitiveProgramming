n = input()
f = [0, 0, 0, 0, 1]
for i in xrange(60):
    f.append(f[-1] + f[-2])
if n < 2:
    print 0, 0, n
else:
    x = f.index(n)
    print f[x-2], f[x-2], f[x-3]
