f = [0 for i in xrange(101)]
f[1] = 1
f[2] = 2

for i in xrange(3, 101):
    f[i] = f[i-1] + f[i-2]

ntest = int(raw_input())
for test in xrange(ntest):
    n = int(raw_input())
    print f[n]
