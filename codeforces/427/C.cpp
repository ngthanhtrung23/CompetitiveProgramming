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

int cur;
int n, m, low[MN], num[MN], cost[MN], nReg, st[MN], top;
bool inReg[MN];
vector<int> ke[MN];
vector<int> reg[MN];

void dfs(int u) {
	st[++top] = u;
	low[u] = num[u] = ++cur;
	REP(i,ke[u].size()) {
		int v = ke[u][i];
		if (inReg[v]) continue;
		if (!num[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else low[u] = min(low[u], num[v]);
	}

	if (low[u] == num[u]) {
		++nReg;
		reg[nReg].clear();
		while (top) {
			int v = st[top--];
			inReg[v] = true;
			// cout << v << ' ';
			reg[nReg].push_back(cost[v]);
			if (v == u) break;
		}
		// cout << endl;
	}
}

int main() {
	ios :: sync_with_stdio(false);
	while (cin >> n) {
		FOR(i,1,n) ke[i].clear();
		memset(low, 0, sizeof low);
		memset(num, 0, sizeof num);
		memset(inReg, false, sizeof inReg);
		nReg = 0;

		FOR(i,1,n) cin >> cost[i];

		cin >> m;
		while (m--) {
			int u, v; cin >> u >> v;
			ke[u].push_back(v);
		}

		cur = 0; top = 0;
		FOR(i,1,n) if (!num[i]) {
			dfs(i);
		}

		int res = 1; long long sum = 0;
		FOR(i,1,nReg) {
			sort(reg[i].begin(), reg[i].end());
			sum += reg[i][0];
			int cur = 1;
			while (cur < reg[i].size() && reg[i][cur] == reg[i][0]) ++cur;
			res = (res * (long long) cur) % 1000000007;
		}

		cout << sum << ' ' << res << endl;
		cout << endl;
	}
	return 0;
}
