import sys

tmp = list(map(int, sys.stdin.readline().split()))
n = tmp[1]
k = tmp[0]

a = list(map(int, sys.stdin.readline().split()))

a.sort()

res = 1000111000
for i in range(0,n-k+1):
    res = min(res, a[i+k-1] - a[i])

print(res)
