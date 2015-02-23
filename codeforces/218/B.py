import Queue

I = lambda: map(int, raw_input().split())
k, n = I()
a = I()

res1 = res2 = 0
q = Queue.PriorityQueue(n)
for x in a:
    q.put(x)
for i in xrange(k):
    x = q.get()
    res2 += x
    if x > 1:
        q.put(x - 1)

q = Queue.PriorityQueue(n)
for x in a:
    q.put(-x)
for i in xrange(k):
    x = q.get()
    res1 -= x
    if x < -1:
        q.put(x + 1)

print res1, res2
