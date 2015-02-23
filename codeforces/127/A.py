I=lambda:map(int,raw_input().split())
n,k=I()
x,y=I()
res=0
for i in xrange(n-1):
    u,v=I()
    res+=((x-u)**2+(y-v)**2)**0.5
    x,y=u,v
print res*k/50.0
