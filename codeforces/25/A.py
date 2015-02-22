n = input()
a = map(int, raw_input().split())
e = sum([x % 2 == 0 for x in a])
print a.index([x for x in a if x % 2 == (e > 1)][0]) + 1
