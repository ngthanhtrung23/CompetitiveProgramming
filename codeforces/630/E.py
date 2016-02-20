x1, y1, x2, y2 = map(int, raw_input().split())

dx = x2 - x1
dy = y2 - y1

if dx % 2 == 0:
	even = dx / 2 + 1
	odd = dx / 2
else:
	even = (dx + 1) / 2
	odd = even

res = 0
if dy % 2 == 0:
	res = even * (dy / 2 + 1) + odd * (dy / 2)
else:
	res = even * (dy / 2 + 1) + odd * (dy / 2 + 1)

print res
