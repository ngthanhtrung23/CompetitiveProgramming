n = input()
for i in range(n+1) + range(n-1, -1, -1):
    nspace = (n - i) * 2 - 1
    if nspace > 0:
        print ' ' * nspace,
    for j in range(i+1) + range(i-1, -1, -1):
        print j,
    print
