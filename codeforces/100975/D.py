with open('strange.in', 'r') as f:
    n = int(f.readline())

n *= 2

res = 1
while n % 2 == 0:
    n /= 2
    res *= 2

with open('strange.out', 'w') as f:
    f.write(str(res) + '\n')
