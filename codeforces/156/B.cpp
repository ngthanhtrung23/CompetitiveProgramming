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

int cnt,n,m,a[100100],pos[100100],neg[100100],P,N,maybe[100100];

int main()
{
	cin >> n >> m;
	fr(i,1,n) 
	{
		cin >> a[i];
		if (a[i]>0) pos[a[i]]++, P++;
		else neg[-a[i]]++, N++;
	}
	
	fr(i,1,n)
		if (pos[i]+N-neg[i]==m) cnt++, maybe[i]=1;
	
	fr(i,1,n)
		if (a[i]>0)
		{
			if (maybe[a[i]]) puts(cnt==1?"Truth":"Not defined");
			else puts("Lie");
		}
		else
		{
			if (maybe[-a[i]]) puts(cnt==1?"Lie":"Not defined");
			else puts("Truth");
		}
}