import fractions

n = int(raw_input())
res = 0

def lcm(a, b):
    return a / fractions.gcd(a, b) * b

def lcm3(a, b, c):
    return lcm(lcm(a, b), c)

for i in xrange(max(1,n-10),n+1):
    for j in xrange(max(1,n-10),n+1):
        for k in xrange(max(1,n-10),n+1):
            res = max(res, lcm3(i, j, k))

print res
