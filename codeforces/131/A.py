s = raw_input()
if len(s) == 1 or s[1:].isupper():
    s = s.swapcase()
print s
