n = raw_input()
x = int(n[0] + n[2] + n[4] + n[3] + n[1]) ** 5
print str(x % 100000).zfill(5)
