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

int n,a[111],num,ans;

int main()
{
	cin >> n;
	fr(i,1,n) cin >> a[i];
	sort(a+1,a+n+1);
	a[0]=10;
	fr(i,1,n)
	{
		a[i]+=a[i-1];
		if (a[i]>720) break;
		num=i; 
		if (a[i]>360) ans+=a[i]-360;
	}
	cout << num << ' ' << ans << endl;
}