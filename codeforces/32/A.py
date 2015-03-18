I = lambda: map(int, raw_input().split())

n, d = I()
a = I()

res = 0
for x in a:
    for y in a:
        if abs(x - y) <= d:
            res += 1
print res - n
