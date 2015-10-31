import fractions
n, a, b = map(int, raw_input().split(' '))

x = a * b / fractions.gcd(a, b)
k = n / x
kx = k * x

good = k * min(a,b) - 1

last = min(n, kx + min(a,b) - 1)
good += last - kx + 1

g = fractions.gcd(good, n)
print '{}/{}'.format(good / g, n / g)
