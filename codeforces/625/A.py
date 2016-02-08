I = lambda: int(raw_input())

n = I()
a = I()
b = I()
c = I()

if a <= b - c:
	print n / a
else:
	res = 0
	if n >= b:
		res += (n - b) / (b - c) + 1
		n -= res * (b - c)
	res += n / a
	print res
