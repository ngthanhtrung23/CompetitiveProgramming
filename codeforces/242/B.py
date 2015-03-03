n = input()
a = []
b = []
for i in xrange(n):
    cur = map(int, raw_input().split())
    a.append(cur[0])
    b.append(cur[1])

min_a = min(a)
max_b = max(b)
for i in xrange(n):
    if min_a == a[i] and max_b == b[i]:
        print i+1
        break
else:
    print -1
