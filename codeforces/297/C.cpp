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

int n, a[100100], b[100100], ansA[100100], ansB[100100];
pair <int,int> s[100100];

int main()
{
	//freopen("c.in", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++) scanf("%d", &s[i].first), s[i].second = i;
	
	sort(s, s + n);
	int k = (n + 2) / 3;
	int common = (n - k) * 2 - n;
	
	for (int i = 0; i < common; i++)
	{
		a[n - 1 - i] = i + 1;
		b[n - 1 - i] = s[n - 1 - i].first - i - 1;
	}
	
	int each = n - k - common;
	for (int i = 0; i < each; i++) 
	{
		b[i] = s[i].first;
		a[i + each] = s[i + each].first;
	}
	
	for (int i = 0; i < n; i++) 
	{
		ansA[s[i].second] = a[i]; 
		ansB[s[i].second] = b[i];
	}
	
	puts("YES");
	for (int i = 0; i < n; i++) printf("%d%c", ansA[i], (i == n - 1 ? '\n' :' '));
	for (int i = 0; i < n; i++) printf("%d%c", ansB[i], (i == n - 1 ? '\n' :' '));
}