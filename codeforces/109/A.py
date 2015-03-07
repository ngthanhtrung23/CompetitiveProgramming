n = input()

min_dig = n
save4 = -1
save7 = -1

for n7 in xrange(n):
    sum4 = n - n7 * 7
    if sum4 < 0:
        break
    if sum4 % 4 == 0:
        n4 = sum4 / 4
        if n4 + n7 < min_dig:
            min_dig = n4 + n7
            save4 = n4
            save7 = n7

if min_dig == n:
    print -1
else:
    print '4' * save4 + '7' * save7
