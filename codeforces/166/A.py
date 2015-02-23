n, k = map(int, raw_input().split())
a = []
for i in xrange(n):
    x, y = map(int, raw_input().split())
    a.append((-x, y, i))
a.sort()
left = right = k-1
while left > 0 and a[left-1][0] == a[left][0] and a[left-1][1] == a[left][1]:
    left -= 1
while right < n-1 and a[right+1][0] == a[right][0] and a[right+1][1] == a[right][1]:
    right += 1
print right - left + 1
