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
using namespace std;

int d[111];

int get(int x)
{
	return x == d[x] ? x : d[x] = get(d[x]);
}

int main()
{
	int test, n, s[111], a[111][111], v[111], x;
	cin >> test;
	while (test--)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> x;
			cin >> v[x] >> s[x];
			for (int j = 0; j < s[x]; j++) cin >> a[x][j];
		}
		
		vector < pair<int,int> > e[111];
		
		for (int x = 0; x < n; x++)
			for (int i = 0; i < s[x]; i++)
			{
				int y = a[x][i];
				if (x < y) e[v[x] + v[y]].push_back(make_pair(x, y));
			}
			
		for (int i = 0; i < n; i++) d[i] = i;
		
		int ans = 0;
		for (int v = 100; v; v--)
			for (int i = 0; i < int(e[v].size()); i++)
			{
				int x = e[v][i].first, y = e[v][i].second;
				x = get(x); y = get(y);
				if (x != y) d[x] = y;
				else ans += v;
			}
			
		cout << ans << endl;
	}
}
