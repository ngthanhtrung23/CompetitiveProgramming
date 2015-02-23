n = input()
sieve = [0] * 3011

for i in xrange(2, 3011):
    if sieve[i] == 0:
        j = i*i
        while j < 3011:
            sieve[j] = i
            j += i

res = 0
for i in xrange(2, n+1):
    u = i
    cnt = 0
    while u > 1:
        p = u if sieve[u] == 0 else sieve[u]
        cnt += 1
        while u % p == 0:
            u /= p
    if cnt == 2:
        res += 1
print res
