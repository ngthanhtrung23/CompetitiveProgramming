I = lambda: map(int, raw_input().split())
n = input()
a = I()
m = input()
b = I()
x = [v / u for u in a for v in b if v % u == 0]
print x.count(max(x))
