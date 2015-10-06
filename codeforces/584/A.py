n, t = map(int, raw_input().split())

fr = 10 ** (n-1)
to = 10**n - 1

while fr % t > 0:
    fr += 1

if fr > to:
    print -1
else:
    print fr
