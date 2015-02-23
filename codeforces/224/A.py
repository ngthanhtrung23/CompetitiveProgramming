import math

x, y, z = map(int, raw_input().split())
p = int(math.sqrt(x*y*z) + 1e-6)
print 4 * (p/x + p/y + p/z)
