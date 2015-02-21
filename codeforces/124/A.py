n, a, b = map(int, raw_input().split())
res = 0
for i in xrange(n):
    before = i
    after = n - i - 1
    if before >= a and after <= b:
        res += 1
print res
