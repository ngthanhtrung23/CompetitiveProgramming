n = input()
a = map(int, raw_input().split())
n_even = sum([x % 2 == 0 for x in a])
if n_even == 1:
    print a.index([x for x in a if x % 2 == 0][0]) + 1
else:
    print a.index([x for x in a if x % 2 == 1][0]) + 1
