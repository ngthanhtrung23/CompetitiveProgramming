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
const int BASE = int(1e9) + 7;

long long fact[1000100], invFact[1000100];

long long power(long long x, long long y)
{
	if (!y) return 1;
	long long res = power(x, y / 2);
	res = res * res % BASE;
	if (y % 2) res = res * x % BASE;
	return res;
}

int isGood(int n, int a, int b)
{
	if (n < 10) return n == a || n == b;
	return isGood(n / 10, a, b) && (n % 10 == a || n % 10 == b);
}

int main()
{
	int a, b, n;
	cin >> a >> b >> n;
	for (int i = 0; i <= n; i++) fact[i] = i ? fact[i - 1] * i % BASE : 1;
	for (int i = 0; i <= n; i++) invFact[i] = power(fact[i], BASE - 2);
	
	long long ans = 0;
	for (int i = 0; i <= n; i++)
		if (isGood(i * a + b * (n - i), a, b))
		{
			ans += fact[n] * invFact[i] % BASE * invFact[n - i];
			ans %= BASE;
		}
	
	cout << ans << endl;
}