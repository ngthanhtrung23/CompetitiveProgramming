a = int(raw_input())
s = oct(a)

res = 0
for c in s:
	if c == '1':
		res += 1
print res
