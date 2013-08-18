import sys

tmp = list(map(int, input().split()))
a = tmp[0]
b = tmp[1]
c = tmp[2]

res = 0
for x in range(0,3):
    if (a >= x and b >= x and c >= x):
        res = max(res, x + (a-x)//3 + (b-x)//3 + (c-x)//3)

print(res)
