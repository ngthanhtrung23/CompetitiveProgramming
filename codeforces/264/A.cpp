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

char s[1000100];
int l[1000100], r[1000100];

void go(int i, int last)
{
	if (i == last) return;
	if (s[i] == 'l') go(i + 1, last);
	printf("%d\n", i + 1);
	if (s[i] == 'r') go(i + 1, last);
}

int main()
{
	scanf("%s", s);
	int n = strlen(s);
	go(0, n);
}