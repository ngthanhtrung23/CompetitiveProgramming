#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <sstream>
#define fr(a,b,c) for (int a=b;a<=c;a++)
#define frr(a,b,c) for (int a=b;a>=c;a--)
#define rep(a,b) for (int a=0;a<b;a++)
#define repp(a,b) for (int a=b-1;a>=0;a--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sz(a) int(a.size())
#define all(a) a.begin(),a.end()
#define pii pair<int,int>
#define oo 1000111222
#define maxN 1
using namespace std;

int n,a[100100],b[100100],c[100100],ans;
priority_queue < pair<int,int> > q;
map <int,int> d;
map <int,int>::iterator it;

int main()
{
	int x;
	cin >> n;
	for (int i=0;i<n;i++) scanf("%d",&x), d[x]++;
	for (it=d.begin();it!=d.end();it++) q.push(mp(it->se,it->fi));
	while (q.size()>2)
	{
		pair <int,int> x,y,z;
		x=q.top(); q.pop();
		y=q.top(); q.pop();
		z=q.top(); q.pop();
		a[++ans]=x.se; b[ans]=y.se; c[ans]=z.se;
		if (--x.fi) q.push(x);
		if (--y.fi) q.push(y);
		if (--z.fi) q.push(z);
	}
	cout << ans << endl;
	for (int i=1;i<=ans;i++) 
	{
		if (b[i]>a[i]) swap(b[i],a[i]);
		if (c[i]>a[i]) swap(c[i],a[i]);
		if (c[i]>b[i]) swap(b[i],c[i]);
		printf("%d %d %d\n",a[i],b[i],c[i]);
	}
}