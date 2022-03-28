#!/usr/bin/env python3

s = input()
s += '001'
n = int(s)

i = 3
p = 1
x = 1

while i < len(s):
    p10 = 10 ** i
    p10_2 = 10**(i-1)

    d = (x*x - n) // p10
    u = x * ((p10 - d % p10) % p10_2)
    x = (x + p10 // 2 * p * u) % (p10 * p10_2)

    l = min(i+i, len(s))
    a = int(s[len(s) - l:])
    d = (p * a - 1) // p10
    u = p * ((p10 - d % p10) % p10)
    p = (p + p10 * u) % (p10 * p10)

    i = 2 * i - 2

print(x % (10 ** len(s)))
