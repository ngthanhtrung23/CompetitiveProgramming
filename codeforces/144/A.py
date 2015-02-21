n = input()
a = map(int, raw_input().split())
res = a.index(max(a)) + a[::-1].index(min(a))
print res - (res >= n)
