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

pair <double,double> a[50500];
int n;

bool cmp(pair <double,double> u, pair <double,double> v)
{
	return u.first * v.second > u.second * v.first;
}

int main()
{
	double ans = 0;
	cin >> n;
	for (int i = 0; i < n; i++) 
	{
		scanf("%lf%lf", &a[i].first, &a[i].second);
		ans += a[i].first;
		a[i].second /= 100;
		a[i].first = a[i].first * a[i].second;
		a[i].second = 1 - a[i].second;
	}
	sort(a, a + n, cmp);
	
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		ans += a[i].second * sum;
		sum += a[i].first;
	}
	
	printf("%.12lf\n", ans);
}