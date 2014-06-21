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

struct Edge {
	int u, v, c;
} edges[MN];

bool operator < (const Edge &a, const Edge &b) {
	return a.c < b.c;
}

int n, m, lab[MN];

int getRoot(int u) {
	return (lab[u] < 0) ? u : lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
	u = getRoot(u); v = getRoot(v);
	if (u == v) return;
	int x = lab[u] + lab[v];
	if (lab[u] < lab[v]) {
		lab[u] = x;
		lab[v] = u;
	}
	else {
		lab[v] = x;
		lab[u] = v;
	}
}

void init() {
	memset(lab, -1, sizeof lab);
}

bool hasDirectPath() {
	FOR(i,1,m) {
		if (edges[i].u == 1 && edges[i].v == n) return true;
		if (edges[i].u == n && edges[i].v == 1) return true;
	}
	return false;
}

bool hasNoPath() {
	init();
	FOR(i,1,m) {
		merge(edges[i].u, edges[i].v);
	}
	return getRoot(1) != getRoot(n);
}

bool check(int val) {
	init();
	FOR(i,1,val) {
		merge(edges[i].u, edges[i].v);
	}

	FOR(i,val+1,m) {
		int u = getRoot(edges[i].u), v = getRoot(edges[i].v);

		if (u == getRoot(1) && v == getRoot(n)) return true;
		if (u == getRoot(n) && v == getRoot(1)) return true;
	}
	return false;
}

int solve() {
	int l = 1, r = m, res = m;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			res = mid;
			r = mid - 1;
		} else l = mid + 1;
	}
	return edges[res].c;
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n >> m) {
		FOR(i,1,m) cin >> edges[i].u >> edges[i].v >> edges[i].c;
		sort(edges+1, edges+m+1);

		if (hasDirectPath()) cout << 0 << endl;
		else if (hasNoPath()) cout << -1 << endl;
		else cout << solve() << endl;
	}
	return 0;
}
