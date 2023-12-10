ntest = int(input())
for test in range(ntest):
    m = int(input())
    assert 1 <= m <= 10**3

    n = input()
    if m == 1:
        min_n = '0'
    else:
        min_n = '1' + ('0' * (m-2)) + '1'

    if len(n) < len(min_n):
        print("NO")
    elif len(n) > len(min_n):
        print("YES")
    elif n >= min_n:
        print("YES")
    else:
        print("NO")
