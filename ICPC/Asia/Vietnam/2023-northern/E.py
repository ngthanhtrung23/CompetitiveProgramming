n = int(input())
res = 1 + n * (n-3) // 2 + n * (n-1) * (n-2) * (n-3) // 24
MOD = 987654321
print(res % MOD)
