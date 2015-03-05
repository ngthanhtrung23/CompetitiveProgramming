# x a b
# c y d
# e f z

# sum
# = x + a + b
# = y + c + d
# = z + e + f
# = x + y + z
# = y + b + e

# 3*sum = 3*(x+y+z) = (x+y+z) + a + b + c + d + e + f
# 2*(x+y+z) == a + b + c + d + e + f
# --> sum

I = lambda: map(int, raw_input().split())
x, a, b = I()
c, y, d = I()
e, f, z = I()

s = (a + b + c + d + e + f) / 2
x = s - a - b
y = s - c - d
z = s - e - f

print x, a, b
print c, y, d
print e, f, z
