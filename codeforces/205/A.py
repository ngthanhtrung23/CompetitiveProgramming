n = input()
a = map(int, raw_input().split())

nn = min(a)
cnt = a.count(nn)

if cnt == 1:
    print a.index(nn) + 1
else:
    print "Still Rozdil"
