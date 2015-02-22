n = input()
if n < 0:
    n = -n
    x1 = n / 10
    x2 = (n / 100) * 10 + n % 10
    n = -min(x1, x2)
print n
