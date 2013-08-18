import sys

tmp = list(map(int, input().split()))
m = tmp[0]
n = tmp[1]

print(m+n-1)

for i in range(1, m+1):
    print(i, 1)

for i in range(2, n+1):
    print(1, i)
