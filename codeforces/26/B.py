s = raw_input()
sum = 0
res = 0
for c in s:
    if c == '(':
        sum += 1
        res += 1
    elif sum > 0:
        sum -= 1
        res += 1
print res - sum
