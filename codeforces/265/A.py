s = raw_input()
t = raw_input()
cur = 0
for c in t:
    if cur < len(s) and s[cur] == c:
        cur += 1
print cur + 1
