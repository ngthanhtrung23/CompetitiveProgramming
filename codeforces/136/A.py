n = input()
a = map(int, raw_input().split())
for i in range(n):
    print a.index(i+1)+1,
