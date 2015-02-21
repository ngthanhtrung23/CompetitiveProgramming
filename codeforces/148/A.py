a = []
for i in xrange(4):
    a.append(int(raw_input()))
d = int(raw_input())
res = 0
for i in xrange(1, d+1):
    if any([i % t == 0 for t in a]):
        res += 1
print res
