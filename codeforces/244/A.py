I = lambda: map(int, raw_input().split())
n, k = I()
a = I()

used = [0] * (n*k + 5)
child = [[] for i in xrange(k)]
for i in xrange(k):
    child[i].append(a[i])
    used[a[i]] = 1

for i in xrange(1, n*k+1):
    if not used[i]:
        j = 0
        while len(child[j]) == n:
            j += 1
        child[j].append(i)

for i in xrange(k):
    for x in child[i]:
        print x,
    print
