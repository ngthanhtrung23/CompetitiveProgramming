s = raw_input()
c = s[-1]
n = int(s[:-1])

move = (n - 1) / 4

turn = ((n - 1) / 4) * 2 + 1
if n % 2 == 0:
	turn += 1

res = (turn - 1) * 7 + move*2 + 1 + 'fedabc'.find(c)
print res
