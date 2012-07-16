#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>
#include <bitset>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; puts("");
using namespace std;
const double PI = acos(-1.0);

int n, sz[5011];
vector<int> ke[5011];
bool mark[5011];

void dfs1(int u, int fu = -1) {
	sz[u] = 1;
	REP(i,ke[u].size()) {
		int v = ke[u][i];
		if (v == fu) continue;
		dfs1(v, u);
		sz[u] += sz[v];
	}
}

int a[5011];
bitset<5011> can;

void dfs2(int u, int fu = -1) {
	REP(i,ke[u].size()) {
		int v = ke[u][i];
		if (v == fu) continue;
		dfs2(v, u);
	}

	int na = 0;
	REP(i,ke[u].size()) {
		int v = ke[u][i];
		if (v == fu) continue;
		a[++na] = sz[v];
	}
	a[++na] = n - sz[u];

	can.reset();
	can.set(0);
	FOR(i,1,na) {
		can = can | (can << a[i]);
	}
	FOR(i,1,n-2) if (can.test(i)) mark[i] = mark[n-i-1] = true;
}

int main() {
	scanf("%d", &n);
	FOR(i,2,n) {
		int u, v; scanf("%d%d", &u, &v);
		ke[u].PB(v); ke[v].PB(u);
	}
	dfs1(1);
	dfs2(1);
	FOR(i,1,n) {
		if (sz[i] < n-1) mark[sz[i]] = mark[n-1-sz[i]] = true;
	}

	int cnt = 0;
	FOR(i,1,n) if (mark[i]) ++cnt;
	cout << cnt << endl;
	FOR(i,1,n) if (mark[i]) {
		printf("%d %d\n", i, n-i-1);
	}
    return 0;
}
