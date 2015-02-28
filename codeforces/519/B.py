from collections import defaultdict

n = input()
I = lambda: map(int, raw_input().split())
a = I()
b = I()
c = I()


def count(a):
    res = defaultdict(int)
    for x in a:
        res[x] += 1
    return res

cnt_a = count(a)
cnt_b = count(b)
cnt_c = count(c)

for x in a:
    if cnt_a[x] > cnt_b[x]:
        print x
        break

for x in b:
    if cnt_b[x] > cnt_c[x]:
        print x
        break
