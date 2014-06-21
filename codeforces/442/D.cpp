#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 1000111;

int n;
int dp[MN], father[MN], ln[MN], ln2[MN];

int main() {
	scanf("%d", &n);
	FOR(i,2,n+1) {
		scanf("%d", &father[i]);
		dp[i] = 1;
		int u = i;
		while (u != 1) {
			if (dp[u] > ln[father[u]]) ln2[father[u]] = ln[father[u]], ln[father[u]] = dp[u];
			else ln2[father[u]] = max(ln2[father[u]], dp[u]);

			u = father[u];
			int cur = max(ln[u], ln2[u] + 1);
			if (cur == dp[u]) break;
			dp[u] = cur;
		}
		printf("%d ", ln[1]);
	}
	return 0;
}
