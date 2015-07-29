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

int n,pos[333][333],ans[333],a[333],have[333],res[333];

int main()
{
	int x,cur=0,cur2=0;
	cin >> n;
	fr(i,1,n) fr(j,1,n) cin >> x, pos[i][x]=j;
	fr(j,1,n) cin >> a[j], pos[0][a[j]]=j;
	fr(i,1,n)
	{
		if (!cur || pos[0][i]<pos[0][cur]) cur2=cur, cur=i;
		else
			if (!cur2 || pos[0][i]<pos[0][cur2]) cur2=i;
		fr(j,1,n) 
		{
			if (cur!=j) x=cur;
			else x=cur2;
			if (!x) continue;
			if (!ans[j]) ans[j]=x, res[j]=i;
			else
				if (pos[j][ans[j]]>pos[j][x]) ans[j]=x, res[j]=i;
		}
	}
	fr(i,1,n) cout << res[i] << ' ';
}