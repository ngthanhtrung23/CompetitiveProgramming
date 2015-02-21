n, bowls, plates = map(int, raw_input().split())
res = 0
a = map(int, raw_input().split())
for typ in a:
    if typ == 1:
        if bowls == 0:
            res += 1
        else:
            bowls -= 1
    else:
        if plates > 0:
            plates -= 1
        elif bowls > 0:
            bowls -= 1
        else:
            res += 1
print res
