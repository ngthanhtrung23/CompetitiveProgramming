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

int n,mn=oo,ans;
pair <int,int> a[101010];

int main()
{
	cin >> n;
	rep(i,n) scanf("%d%d",&a[i].se,&a[i].fi), a[i].fi=-a[i].fi;
	sort(a,a+n);
	rep(i,n)
	{
		ans+=mn<a[i].se;
		mn=min(mn,a[i].se);
	}
	cout << ans << endl;	
}