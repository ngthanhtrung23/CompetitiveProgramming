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

const int MN = 1011;

#define y0 y0__
#define y1 y1__

char a[MN][MN];
int m, n, v, x0, y0, x1, y1;

int first, last, qu[MN*MN], qv[MN*MN], fromF[MN][MN];

int dist(int x0, int y0, int x1, int y1) {
	return abs(x0 - x1) + abs(y0 - y1);
}

bool outside(int u, int v) {
	return u < 1 || v < 1 || u > m || v > n;
}

const int di[] = {-1,1,0,0,-2,2,0,0,1,1,-1,-1};
const int dj[] = {0,0,-1,1,0,0,-2,2,1,-1,1,-1};

bool visited[MN][MN];

bool dfs() {
	int bound = v / 2;
	if (v % 2 == 0) --bound;
	FOR(i,1,m) FOR(j,1,n) if (fromF[i][j] <= bound) a[i][j] = 'F';
	memset(visited, false, sizeof visited);

	// FOR(i,1,m) {
		// PR(a[i], n);
	// }

	first = 1; last = 0;
	FOR(i,1,m) FOR(j,1,n) if (fromF[i][j] == 0 && dist(i,j,x0,y0) <= v) {
		++last;
		qu[last] = i;
		qv[last] = j;
		visited[i][j] = true;
	}

	bound = 4;
	if (v % 2 == 0) bound = 12;
	while (first <= last) {
		int u = qu[first], v = qv[first]; ++first;

		REP(dir, bound) {
			int uu = u + di[dir], vv = v + dj[dir];
			if (outside(uu, vv)) continue;

			if (a[uu][vv] != 'F') continue;
			if (visited[uu][vv]) continue;

			++last;
			qu[last] = uu;
			qv[last] = vv;
			visited[uu][vv] = true;
		}
	}

	// FOR(i,1,m) {
		// PR(visited[i], n);
	// }

	FOR(i,1,m) FOR(j,1,n) if (visited[i][j] && fromF[i][j] == 0 && dist(i,j,x1,y1) <= v) {
		return true;
	}
	return false;
}

bool solve() {
	if (dist(x0, y0, x1, y1) <= v) return true;

	memset(fromF, -1, sizeof fromF);
	first = 1; last = 0;
	FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'F') {
		++last;
		qu[last] = i;
		qv[last] = j;

		fromF[i][j] = 0;
	}
	while (first <= last) {
		int u = qu[first], v = qv[first]; ++first;
		REP(dir,4) {
			int uu = u + di[dir], vv = v + dj[dir];
			if (outside(uu, vv)) continue;

			if (fromF[uu][vv] >= 0) continue;
			fromF[uu][vv] = fromF[u][v] + 1;
			++last;
			qu[last] = uu;
			qv[last] = vv;
		}
	}

	// FOR(i,1,m) {
		// PR(fromF[i], n);
	// }

	if (last == 0) return false;

	if (fromF[x0][y0] > v || fromF[x1][y1] > v) return false;
	return dfs();
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> m >> n >> v) {
		cin >> x0 >> y0 >> x1 >> y1;
		FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

		if (solve()) puts("Hello, Deimos!");
		else puts("Dire victory");
	}
	return 0;
}
