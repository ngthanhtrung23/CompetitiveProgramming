n = raw_input()
s = raw_input()
last = ' '
res = 0
for c in s:
    if last == c:
        res += 1
    else:
        last = c
print res
