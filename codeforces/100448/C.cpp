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

int n, a[10111], first[10111];
map<int,int> cnt;
int b[10111], m;

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n) {
		FOR(i,1,n) cin >> a[i];
		sort(a+1, a+n+1);
		cnt.clear();

		m = 0;
		FOR(i,1,n) if (cnt[a[i]] < 3) {
			++cnt[a[i]];
			b[++m] = a[i];
		}
		// PR(b, m);

		long long res = -1;
		FOR(i,1,m-3) {
			if (b[i+3] < b[i] + b[i+1] + b[i+2])
				res = max(res, (long long) b[i] + b[i+1] + b[i+2] + b[i+3]);
		}
		cout << res << endl;
	}
	return 0;
}
