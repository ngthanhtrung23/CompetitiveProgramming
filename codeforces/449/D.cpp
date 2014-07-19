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
const int MOD = 1000000007;

int n, a[MN], cnt[1<<21], p2[MN];

int main() {
	ios :: sync_with_stdio(false);
	p2[0] = 1;
	FOR(i,1,MN-1) p2[i] = (p2[i-1] + p2[i-1]) % MOD;

	while (cin >> n) {
		memset(cnt, 0, sizeof cnt);
		FOR(i,1,n) {
			cin >> a[i];
			cnt[a[i]]++;
		}

		REP(i,20)
			REP(j,1<<20)
			if (j >> i & 1)
				cnt[j-(1<<i)] += cnt[j];

		long long res = 0;
		REP(i,1<<20) {
			if (__builtin_popcount(i) % 2 == 1)
				res = (res - p2[cnt[i]] + 1 + MOD) % MOD;
			else
				res = (res + p2[cnt[i]] - 1 + MOD) % MOD;
		}
		cout << res << endl;
	}
	return 0;
}
