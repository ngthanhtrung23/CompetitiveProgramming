import math

n = int(raw_input())

def C(n,k):
	return math.factorial(n) / math.factorial(k) / math.factorial(n-k)

print C(n+4, n-1) * C(n+2, n-1)
