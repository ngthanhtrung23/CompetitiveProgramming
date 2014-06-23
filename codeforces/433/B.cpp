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

long long a[2][100111];

int main() {
	ios :: sync_with_stdio(false);
	int n;
	while (cin >> n) {
		FOR(i,1,n) {
			cin >> a[0][i];
			a[1][i] = a[0][i];
		}
		sort(a[1] + 1, a[1] + n + 1);

		FOR(i,1,n) {
			a[0][i] += a[0][i-1];
			a[1][i] += a[1][i-1];
		}
		int q; cin >> q;
		while (q--) {
			int typ, u, v;
			cin >> typ >> u >> v;
			if (typ == 1) cout << a[0][v] - a[0][u-1];
			else cout << a[1][v] - a[1][u-1];
			cout << "\n";
		}
	}
	return 0;
}
