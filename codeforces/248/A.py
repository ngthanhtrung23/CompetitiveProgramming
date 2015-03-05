n = input()
a = []
b = []
for i in xrange(n):
    u, v = map(int, raw_input().split())
    a.append(u)
    b.append(v)
print min(sum(a), n - sum(a)) + min(sum(b), n - sum(b))
