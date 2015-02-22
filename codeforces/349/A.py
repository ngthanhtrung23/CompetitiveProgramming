n = input()
c25 = 0
c50 = 0
for x in map(int, raw_input().split()):
    if x == 25:
        c25 += 1
    elif x == 50:
        c25 -= 1
        if c25 < 0:
            print 'NO'
            break
        c50 += 1
    else:
        if c50 > 0 and c25 > 0:
            c50 -= 1
            c25 -= 1
        elif c25 >= 3:
            c25 -= 3
        else:
            print 'NO'
            break
else:
    print 'YES'
