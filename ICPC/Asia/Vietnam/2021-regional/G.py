#!/usr/bin/env python3


def get_bit(mask, bit):
    return (mask >> bit) & 1


n = int(input())
ids = [i ^ (i>>1) for i in range(1, n+1)]


for bit in range(10):
    people = [i+1 for i in range(n) if get_bit(ids[i], bit) == 1]
    print(len(people))
    print(' '.join(map(str, people)))


positives = 0
for bit in range(10):
    s = input()
    if s[0] == 'P':
        positives += 2**bit

for i in range(n):
    if ids[i] == positives:
        print(i+1)
        break
else:
    print(-1)
