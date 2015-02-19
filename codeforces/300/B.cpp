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

int d[100];
vector <int> a[100];

int get(int x)
{
	return x == d[x] ? x : d[x] = get(d[x]);
}

int main()
{
	int n, m, x, y;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) d[i] = i;
	while (m--) 
	{
		cin >> x >> y;
		d[get(x)] = get(y);
	}
	
	for (int i = 1; i <= n; i++) a[get(i)].push_back(i);
	
	vector <int> p1;
	vector < pair<int,int> > p2;
	
	for (int i = 1; i <= n; i++)
		if (a[i].size() > 3)
		{
			puts("-1");
			return 0;
		}
		else
			if (a[i].size() == 1) p1.push_back(i);
			else 
				if (a[i].size() == 2) p2.push_back(make_pair(a[i][0], a[i][1]));
		
	if (p2.size() > p1.size()) 
	{
		puts("-1"); return 0;
	}
	
	for (int i = 1; i <= n; i++)
		if (a[i].size() == 3)
			for (int j = 0; j < 3; j++)	
				cout << a[i][j] << (j == 2 ? '\n' : ' ');
	
	for (int i = 0; i < int(p2.size()); i++)
		cout << p2[i].first << ' ' << p2[i].second << ' ' << p1[i] << endl;
		
	for (int i = p2.size(); i < int(p1.size()); i += 3)
		cout << p1[i] << ' ' << p1[i + 1] << ' ' << p1[i + 2] << endl;
}