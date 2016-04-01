m,n,t=map(int,raw_input().split())
c=[0]*n
r,kitten=0,0
for i in xrange(m):
	s=raw_input()
	for j in xrange(n):
		if s[j]=='Y':
			c[j]+=1
			if c[j]==t:
				r+=1
print r
