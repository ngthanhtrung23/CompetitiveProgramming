n, need = map(int, raw_input().split())
a = raw_input()

f = [[[False for i in xrange(2)] for j in xrange(111)] for k in xrange(111)]

if need == 0:
    f[0][0][1] = True
else:
    f[0][0][0] = True

for i in xrange(n):
    for j in xrange(i+1):
        for k in xrange(2):
            if f[i][j][k]:
                i2 = i + 1
                if a[i] == 'Y' or a[i] == '?':
                    j2 = 0
                    k2 = k
                    f[i2][j2][k2] = True
                if a[i] == 'N' or a[i] == '?':
                    j2 = j + 1
                    if j2 <= need:
                        k2 = k
                        if j2 == need:
                            k2 = 1
                        f[i2][j2][k2] = True

res = False
for j in xrange(need + 1):
    if f[n][j][1]:
        res = True

if res:
    print 'YES'
else:
    print 'NO'
