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

int n,k,d[256][256],ans;
pair <char,int> a[100100];
string s;

int main()
{
	cin >> s >> k;
	while (k--)
	{
		string t;
		cin >> t;
		d[t[0]][t[1]]=d[t[1]][t[0]]=1;
	}
	char cur=s[0];
	int cnt=1;	
	s+='A';
	fr(i,1,sz(s)-1)
		if (s[i]!=cur) a[n++]=make_pair(cur,cnt), cur=s[i], cnt=1;
		else cnt++;
	for (int i=0;i+1<n;)
		if (d[a[i].fi][a[i+1].fi]) 
		{
			int x=a[i].se,y=a[i+1].se,j;
			for (j=i+2;j<n;j++)
				if (!d[a[j-1].fi][a[j].fi]) break;
				else 
					if ((j-i)&1) y+=a[j].se;
					else x+=a[j].se;
			i=j;
			ans+=min(x,y);
		}
		else i++;
	cout << ans << endl;
}