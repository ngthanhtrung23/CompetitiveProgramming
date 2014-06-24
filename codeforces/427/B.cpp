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

const int MN = 400111;
int n, t, c, a[MN], l[MN], r[MN];

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n >> t >> c) {
		FOR(i,1,n) cin >> a[i];
		FOR(i,1,n) {
			if (c == 1 || i == 1 || i % c == 1) l[i] = a[i];
			else l[i] = max(l[i-1], a[i]);
		}
		FORD(i,n,1) {
			if (c == 1 || i == n || i % c == 0) r[i] = a[i];
			else r[i] = max(r[i+1], a[i]);
		}

		int res = 0;
		FOR(i,1,n-c+1) {
			int j = i + c - 1;
			if (max(l[j], r[i]) <= t) ++res;
		}
		cout << res << endl;
	}
	return 0;
}
