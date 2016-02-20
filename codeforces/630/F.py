import math

n = int(raw_input())

def C(n,k):
	return math.factorial(n) / math.factorial(k) / math.factorial(n-k)

print C(n, 5) + C(n, 6) + C(n, 7)
