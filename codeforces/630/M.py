x = int(raw_input())
x %= 360

if x <= 45:
	print 0
elif x <= 135:
	print 1
elif x <= 225:
	print 2
elif x <= 314:
	print 3
else:
	print 0
