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
	int n, h[33], a[33], ans = 0;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> h[i] >> a[i];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ans += h[i] == a[j];
	cout << ans << endl;
}