n = input()
a = map(int, raw_input().split())
print n if sum(a) % n == 0 else n-1
