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

int main()
{
	int n, p[100100];
	cin >> n;
	
	if ((n / 2) % 2) 
	{
		puts("-1");
		return 0;
	}
	
	for (int i = 1; i < n / 2; i += 2)
	{
		p[i] = i + 1;
		p[i + 1] = n - i + 1;
		p[n - i + 1] = n - i;
		p[n - i] = i;
	}
	if (n % 2) p[n / 2 + 1] = n / 2 + 1;
	
	for (int i = 1; i <= n; i++) cout << p[i] << (i == n?'\n':' ');
}