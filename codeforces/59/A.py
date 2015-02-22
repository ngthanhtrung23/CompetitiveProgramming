s = raw_input()
if sum(map(str.islower, s)) < sum(map(str.isupper, s)):
    print s.upper()
else:
    print s.lower()
