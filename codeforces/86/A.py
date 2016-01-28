def get(n):
	saven = n
	revn = 0

	p10 = 1
	while n > 0:
		revn = revn + (9 - n % 10) * p10
		p10 *= 10
		n /= 10

	return saven * revn

l, r = map(int, raw_input().split())

res = max(get(l), get(r))

cur = 5
for turn in xrange(15):
	if l <= cur <= r:
		res = max(res, get(cur))
	cur *= 10

print res
