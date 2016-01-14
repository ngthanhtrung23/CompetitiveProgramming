l, r, k = map(int, raw_input().split())

res = [str(k**i) for i in xrange(64) if l <= k**i <= r]
if len(res) == 0:
	print -1
else:
	print ' '.join(res)
