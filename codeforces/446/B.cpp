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

int a[1011][1011], m, n, k, p, row[1011], col[1011];
long long delRow[1000111], delCol[1000111];

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> m >> n >> k >> p) {
		FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
		memset(row, 0, sizeof row);
		memset(col, 0, sizeof col);

		multiset<int> rows, cols;
		FOR(i,1,m) FOR(j,1,n) {
			row[i] += a[i][j];
			col[j] += a[i][j];
		}
		FOR(i,1,m) rows.insert(-row[i]);
		FOR(j,1,n) cols.insert(-col[j]);

		long long res = 0;
		FOR(i,0,k) {
			delRow[i] = res;
			long long best = *rows.begin();
			res -= best;
			best += n * p;

			rows.erase(rows.begin());
			rows.insert(best);
		}

		res = 0;
		FOR(i,0,k) {
			delCol[i] = res;
			long long best = *cols.begin();
			res -= best;
			best += m * p;

			cols.erase(cols.begin());
			cols.insert(best);
		}

		// PR0(delRow, k+1);
		// PR0(delCol, k+1);

		res = -1000111000111000111LL;
		FOR(x,0,k) {
			long long cur = delRow[x] + delCol[k-x] - x * p * (long long) (k-x);
			res = max(res, cur);
		}
		cout << res << endl;
	}
	return 0;
}
