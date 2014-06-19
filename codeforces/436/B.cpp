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

int m, n, k;
char a[2011][2011];

int main() {
	ios :: sync_with_stdio(false);

	while (cin >> m >> n >> k) {
		FOR(i,1,m) FOR(j,1,n) {
			cin >> a[i][j];
		}
		FOR(j,1,n) {
			int res = 0;
			FOR(i,1,m) if (a[i][j] == 'U' && i % 2 == 1) ++res;

			for(int i = 1, jj = j; i <= m && jj <= n; ++i, ++jj)
				if (a[i][jj] == 'L')
					++res;

			for(int i = 1, jj = j; i <= m && jj >= 1; ++i, --jj)
				if (a[i][jj] == 'R')
					++res;

			cout << res << ' ';
		}
		cout << endl;
	}
	return 0;
}
