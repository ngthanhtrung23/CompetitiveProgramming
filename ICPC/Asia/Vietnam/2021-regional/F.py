#!/usr/bin/env python3


MOD = 10**9 + 7

n, k = map(int, input().split())
print(2**(k-1) * (n-k+1) % MOD)
