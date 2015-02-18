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

int m, n, k;
map <int,int> a;

int main()
{
	int x;
	cin >> m >> n >> k;
	for (int i = 0; i < m; i++) scanf("%d", &x), a[-x]++;
	for (int i = 0; i < n; i++) scanf("%d", &x), a[-x]--;
	
	int reserve = 0, ans = 0;
	for (map <int,int>::iterator it = a.begin(); it != a.end(); it++)
		if (it -> second < 0) reserve -= it -> second;
		else
		{
			if (it -> second > reserve)
			{
				ans = 1; break;
			}
			reserve -= it -> second;
		}
			
	puts(ans ? "YES" : "NO");
}