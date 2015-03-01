n = input()
a = []

for i in xrange(n):
    a.append(map(int, raw_input().split()))

sum_rows = [sum(x) for x in a]
sum_cols = [sum(i) for i in zip(*a)]

res = 0
for i in xrange(n):
    for j in xrange(n):
        if sum_cols[j] > sum_rows[i]:
            res += 1
print res
