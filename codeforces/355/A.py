k, d = map(int, raw_input().split())
if d == 0:
    if k == 1:
        print 0
    else:
        print 'No solution'
else:
    print chr(ord('0') + d) + ('0' * (k-1))
