x = int(raw_input())

def f(m, n):
	return 6*m*n*n - 3*(m+n)*(n-1)*n + (n-1)*n*(2*n-1)

all = []
for n in xrange(1,int(1.5*10**6 + 1)):
	if (6*x) % n > 0:
		continue
	l = n
	r = x
	res = l
	while l <= r:
		mid = (l + r) / 2
		if f(mid, n) <= 6*x:
			res = mid
			l = mid + 1
		else:
			r = mid - 1
	if f(res, n) == 6*x:
		all.append((res, n))
		if res != n:
			all.append((n, res))

all = sorted(all, key = lambda x: (x[0], x[1]))
print len(all)
for p in all:
	print p[0], p[1]
