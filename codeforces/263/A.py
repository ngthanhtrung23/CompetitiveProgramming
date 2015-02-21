d = [2, 1, 0, 1, 2]
for i in d:
    s = raw_input().split()
    try:
        if s.index('1') >= 0:
            print i + d[s.index('1')]
    except ValueError:
        pass
