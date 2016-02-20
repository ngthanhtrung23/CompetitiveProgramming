import math

n = int(raw_input())

def C(n,k):
	return math.factorial(n) / math.factorial(k) / math.factorial(n-k)

all = n * 2 - 2

res = 0
for i in xrange(all):
	left = i
	right = i + n - 1
	if right >= all:
		continue

	cur = 4
	other = all - n
	if left > 0:
		cur *= 3
		other -= 1
	if right < all - 1:
		cur *= 3
		other -= 1
	res += cur * (4**other)
print res
