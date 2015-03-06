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
#define reset(a,b) memset(a,b,sizeof(a))
#define pii pair<int,int>
#define oo 1000111222
#define maxN 1
using namespace std;

int x[1000100],y[1000100],d[256];

int main()
{
	string a,b;
	int N,m,n,X=0,Y=0,A=0,B=0,lcm;
	d['R']=0; d['S']=1; d['P']=2;
	cin >> N >> a >> b;
	m=sz(a); n=sz(b);
	fr(i,1,1000000)	
		if (i%m==0 && i%n==0) 
		{
			lcm=i; break;
		}
	rep(i,lcm)
		if (a[i%m]!=b[i%n]) 
		{
			int t=d[a[i%m]],u=d[b[i%n]];
			if ((t+1)%3==u) x[i]=1, A++;
			else y[i]=1, B++;
		}
	X=N/lcm*A; Y=N/lcm*B;
	rep(i,N%lcm) X+=x[i], Y+=y[i];
	cout << Y << ' ' << X << endl;
}

