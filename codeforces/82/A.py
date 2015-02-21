friends = ["Sheldon", "Leonard", "Penny", "Rajesh", "Howard"]
cur = 5
n = int(raw_input())
while n > cur:
    n -= cur
    cur *= 2
print friends[(n - 1) / (cur / 5)]
