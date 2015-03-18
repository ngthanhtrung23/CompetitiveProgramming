s = raw_input()
n = len(s)
i = 0

res = ''
while i < n:
    if s[i] == '.':
        res += '0'
        i += 1
    else:
        res += '1' if s[i+1] == '.' else '2'
        i += 2
print res
