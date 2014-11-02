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
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;

int n, m, parity[MN];
vector<int> ke[MN], cur;
bool hasOdd, visited[MN];

void dfs(int u, int fu = -1) {
    if (parity[u] == 1) hasOdd = true;

    visited[u] = true;
    cur.push_back(u); parity[u] = 1 - parity[u];
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (visited[v] || v == fu) continue;

        dfs(v, u);
        cur.push_back(u);
        parity[u] = 1 - parity[u];
    }

    if (parity[u] == 1) {
        if (fu == -1) {
            cur.erase(cur.begin());
        }
        else {
            cur.push_back(fu); parity[fu] = 1 - parity[fu];
            cur.push_back(u); parity[u] = 1 - parity[u];
        }
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        FOR(i,1,n) cin >> parity[i];
        memset(visited, 0, sizeof visited);

        vector<int> res;
        int cnt = 0;
        FOR(i,1,n) if (!visited[i]) {
            cur.clear();
            hasOdd = false;
            dfs(i);
            if (hasOdd) {
                ++cnt;
                res = cur;
            }
        }
        if (cnt > 1) {
            cout << -1 << endl;
            continue;
        }
        if (cnt == 0) {
            cout << 0 << endl;
            continue;
        }
        cout << res.size() << endl;
        REP(i,res.size()) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}
