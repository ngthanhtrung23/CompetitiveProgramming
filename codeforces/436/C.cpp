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

char a[1011][11][11];
int lab[1011], nEdges;
pair<int, pair<int,int> > edges[1011*1011];
int m, n, k, w, nSave;
vector<int> ke[1011];

int getRoot(int u) {
	if (lab[u] < 0) return u;
	else return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
	int x = lab[u] + lab[v];
	lab[u] = x;
	lab[v] = u;
}

void addEdge(int u, int v, int c) {
	++nEdges;
	edges[nEdges] = make_pair(c, make_pair(u, v));
}

void init() {
	nEdges = 0;
	FOR(i,1,k) {
		addEdge(0, i, m*n);
		FOR(j,i+1,k) {
			int cnt = 0;
			FOR(u,1,m) FOR(v,1,n)
				if (a[i][u][v] != a[j][u][v]) ++cnt;
			addEdge(i, j, cnt * w);
		}
	}
}

int solve() {
	memset(lab, -1, sizeof lab);
	sort(edges+1, edges+nEdges+1);

	int res = 0;
	FOR(i,0,k) ke[i].clear();
	FOR(i,1,nEdges) {
		int u = edges[i].second.first, v = edges[i].second.second;
		u = getRoot(u); v = getRoot(v);
		if (u == v) continue;

		res += edges[i].first;
		merge(u, v);

		u = edges[i].second.first, v = edges[i].second.second;
		ke[u].push_back(v);
		ke[v].push_back(u);
	}
	return res;
}

bool ok[2011];

void dfs(int u) {
	ok[u] = true;
	REP(i,ke[u].size()) {
		int v = ke[u][i];
		if (ok[v]) continue;

		cout << v << ' ' << u << endl;
		dfs(v);
	}
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> m >> n >> k >> w) {
		FOR(level,1,k) {
			FOR(i,1,m) FOR(j,1,n) cin >> a[level][i][j];
		}
		init();
		cout << solve() << endl;
		memset(ok, false, sizeof ok);
		dfs(0);
	}
	return 0;
}
