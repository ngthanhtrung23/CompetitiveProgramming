n_test = int(raw_input())

for test in xrange(n_test):
    x1, y1, x2, y2 = map(int, raw_input().split(' '))
    dx = x1 - x2
    if dx < 0:
        dx = -dx
    dy = y1 - y2
    if dy < 0:
        dy = -dy

    if dx > dy:
        dx, dy = dy, dx

    res = 2 * dy - (dy - dx) % 2
    print(res)
