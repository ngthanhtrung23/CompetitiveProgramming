n, k = map(int, raw_input().split())
if k > n:
    print -1
elif k == 1:
    if n == 1:
        print 'a'
    else:
        print -1
else:
    n -= k-2
    print 'ab' * (n/2) + ('a' if n % 2 == 1 else '') + ''.join(map(chr, range(ord('c'), ord('a')+k)))
