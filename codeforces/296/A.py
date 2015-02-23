n = input()
a = map(int, raw_input().split())
cnt = [0] * 1011
for x in a:
    cnt[x] += 1
if max(cnt) <= (n+1)/2:
    print 'YES'
else:
    print 'NO'
