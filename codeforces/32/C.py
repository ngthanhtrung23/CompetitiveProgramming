n, m, s = map(int, raw_input().split())

e1 = n % s
e2 = m % s

if e1 == 0:
    e1 = s

if e2 == 0:
    e2 = s

e1 *= (n - 1) / s + 1
e2 *= (m - 1) / s + 1

print e1 * e2
