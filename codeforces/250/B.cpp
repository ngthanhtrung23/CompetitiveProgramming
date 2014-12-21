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

void recover(string s)
{
	vector <string> a;
	string t="";
	rep(i,sz(s))
		if (s[i]!=':') t+=s[i];
		else 
		{
			if (i || t!="") a.pb(t); 
			t="";
		}
	if (t!="") a.pb(t);
		
	int rest=9-sz(a),cnt=0;
	rep(i,sz(a))
		if (a[i]=="")
			rep(j,rest) 
			{
				cout << "0000";
				if (++cnt<8) cout << ':';
			}
		else
		{
			rep(j,4-sz(a[i])) cout << 0;
			cout << a[i];
			if (++cnt<8) cout << ':';
		}
	puts("");
}

int main()
{
	int test;
	string s;
	cin >> test;
	while (test--)
	{
		cin >> s;
		recover(s);
	}
}