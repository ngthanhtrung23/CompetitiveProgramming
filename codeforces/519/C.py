a, b = map(int, raw_input().split())
l = 0
r = min(a, b)
res = 0


def check(t):
    if t > a or t > b:
        return False
    aa = a - t
    bb = b - t
    return aa + bb >= t

while l <= r:
    mid = (l + r) / 2
    if check(mid):
        res = mid
        l = mid + 1
    else:
        r = mid - 1
print res
