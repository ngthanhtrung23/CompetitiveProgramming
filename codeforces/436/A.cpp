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

int n, x;
struct Candy {
	int t, h, m;
} a[2011];

bool operator < (const Candy &a, const Candy &b) {
	return a.m > b.m;
}
bool eaten[2011];

int go(int need) {
	int maxH = x, res = 0;
	FOR(turn,1,2000) {
		FOR(i,1,n) if (a[i].t == need && a[i].h <= maxH && !eaten[i]) {
			eaten[i] = true;
			maxH += a[i].m;
			need = 1 - need;

			++res;
			break;
		}
	}
	return res;
}

int main() {
	while (cin >> n >> x) {
		FOR(i,1,n) {
			cin >> a[i].t >> a[i].h >> a[i].m;
		}
		sort(a+1, a+n+1);
		int res = 0;
		memset(eaten, false, sizeof eaten);
		res = max(res, go(0));
		memset(eaten, false, sizeof eaten);
		res = max(res, go(1));

		cout << res << endl;
	}
}
