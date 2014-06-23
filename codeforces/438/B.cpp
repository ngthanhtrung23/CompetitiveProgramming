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

int a[MN], lab[MN];
struct Edge {
	int u, v, c;
} edges[MN];

bool operator < (const Edge &a, const Edge &b) {
	return a.c > b.c;
}

int getRoot(int u) {
	return (lab[u] < 0) ? u : lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
	lab[u] = lab[u] + lab[v];
	lab[v] = u;
}

int m, n;

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n >> m) {
		FOR(i,1,n) cin >> a[i];
		FOR(i,1,m) {
			cin >> edges[i].u >> edges[i].v;
			edges[i].c = min(a[edges[i].u], a[edges[i].v]);
		}
		sort(edges+1, edges+m+1);

		long double cnt = 0;
		long double sum = 0.0;

		memset(lab, -1, sizeof lab);

		FOR(i,1,m) {
			int u = edges[i].u, v = edges[i].v;
			u = getRoot(u); v = getRoot(v);

			if (u == v) continue;

			cnt += lab[u] * (long long) lab[v];
			sum += lab[u] * (long long) lab[v] * edges[i].c;
			merge(u, v);
		}
		cout << (fixed) << setprecision(6) << (sum / cnt) << endl;
	}
	return 0;
}
