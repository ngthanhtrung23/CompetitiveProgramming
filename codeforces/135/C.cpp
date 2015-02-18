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

int n,x,y,z,X,Y,px=-1,py=-1,pz=-1,pzz=-1;
string s,t;
set <string> ans;
set <string>::iterator it;

int ok(int a,int b)
{
	return a>=0 && a<=b;
}

int main()
{
	cin >> s;
	n=sz(s);
	t=s.substr(n-2,2);
	X=(n-2)/2; Y=n-2-X;
	rep(i,n) 
		if (s[i]=='0') x++, px=i;
		else 
			if (s[i]=='1') y++, py=i;
			else z++, pzz=pz, pz=i;
	if (x+z>=X+2) ans.insert("00");
	if (y+z>=Y+2) ans.insert("11");
	if (pz<0 && ok(X+1-x,z) && ok(Y+1-y,z)) ans.insert(px<py?"01":"10");
	else 
		for (char c='0';c<='1';c++)
		{
			int xx=x+(c=='0'),yy=y+(c=='1'),pxx=px,pyy=py;
			if (c=='0') pxx=max(pxx,pz);
			else pyy=max(pyy,pz);
			if (pzz<0 && ok(X+1-xx,z-1) && ok(Y+1-yy,z-1)) ans.insert(pxx<pyy?"01":"10");
			else
				for (char cc='0';cc<='1';cc++)
				{
					int xxx=xx+(cc=='0'),yyy=yy+(cc=='1'),pxxx=pxx,pyyy=pyy;
					if (cc=='0') pxxx=max(pxxx,pzz);
					else pyyy=max(pyyy,pzz);
					if (ok(X+1-xxx,z-2) && ok(Y+1-yyy,z-2)) ans.insert(pxx<pyy?"01":"10");
				}
		}
	for (it=ans.begin();it!=ans.end();it++) cout << *it << endl;
}