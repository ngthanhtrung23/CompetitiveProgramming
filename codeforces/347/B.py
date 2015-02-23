n = input()
a = map(int, raw_input().split())

cnt = 0
good = False
for i in xrange(n):
    if a[i] == i:
        cnt += 1
    elif a[a[i]] == i:
        good = True

if good:
    cnt += 2
elif cnt < n:
    cnt += 1

print cnt
