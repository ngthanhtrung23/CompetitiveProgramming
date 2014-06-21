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

const int MN = 100111;

int n, a[MN];
long long dp[MN];

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n) {
		FOR(i,1,n) cin >> a[i];
		sort(a+1, a+n+1);

		dp[0] = 0; dp[1] = 1000111000111000111LL;
		FOR(i,2,n) {
			dp[i] = dp[1];
			FOR(j,max(0,i-10),i-2) {
				long long cur = dp[j];
				int mid = (i + j + 1) >> 1;
				FOR(x,j+1,i) cur += abs(a[x] - a[mid]);
				dp[i] = min(dp[i], cur);
			}
		}
		cout << dp[n] << endl;
	}
	return 0;
}
