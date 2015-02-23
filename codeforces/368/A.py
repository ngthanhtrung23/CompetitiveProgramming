import Queue

n, d = map(int, raw_input().split())
a = map(int, raw_input().split())
m = input()

q = Queue.PriorityQueue(n)
for x in a:
    q.put(x)

res = 0
for i in xrange(m):
    if q.empty():
        res -= d
    else:
        res += q.get()
print res
