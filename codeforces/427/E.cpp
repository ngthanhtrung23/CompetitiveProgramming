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
int n, m, a[MN];

long long f(long long x) {
	long long res = 0;
	if (x >= a[1]) { // There's something on the left
		int from = 1, to = 1;
		FOR(i,1,n) if (a[i] <= x) to = i;

		int cur = from;
		while (cur <= to) {
			res += llabs(x - a[cur]) * 2LL;
			cur += m;
		}
	}
	if (x <= a[n]) {
		int from, to = n;
		FORD(i,n,1) if (a[i] >= x) from = i;

		int cur = to;
		while (cur >= from) {
			res += llabs(x - a[cur]) * 2LL;
			cur -= m;
		}
	}
	return res;
}

long long get(long long l, long long r) {
	long long res = min(f(l), f(r));
	while (l < r) {
		long long x1 = (l+l+r) / 3;
		long long x2 = (l+r+r) / 3;
		long long y1 = f(x1), y2 = f(x2);

		res = min(res, min(y1, y2));
		if (y1 < y2) r = x2-1;
		else l = x1+1;
	}
	return res;
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n >> m) {
		FOR(i,1,n) cin >> a[i];
		sort(a+1, a+n+1);
		cout << get(-(1e9+5), 1e9+5) << endl;
	}
	return 0;
}
