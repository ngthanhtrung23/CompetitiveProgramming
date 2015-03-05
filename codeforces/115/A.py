n = input()
ke = [[] for i in xrange(n)]
root = []
cache = [-1 for i in xrange(n)]


def dfs(u, fu):
    if cache[u] >= 0:
        return cache[u]
    res = 1
    for v in ke[u]:
        res = max(res, dfs(v, u) + 1)
    cache[u] = res
    return res

for i in xrange(n):
    fi = input()
    if fi == -1:
        root.append(i)
    else:
        ke[fi-1].append(i)
print max([dfs(x, -1) for x in root])
