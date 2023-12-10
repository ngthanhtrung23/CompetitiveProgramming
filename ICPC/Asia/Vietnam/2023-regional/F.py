def f(s):
    return sorted(s[0::2]) + sorted(s[1::2])

ntest = int(input())
for _ in range(ntest):
    a = input()
    b = input()

    print("YES" if f(a) == f(b) else "NO")
