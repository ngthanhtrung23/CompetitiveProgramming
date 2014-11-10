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

const int MN = 400111;
int n, q, a[MN], h[MN], getIn[MN], getOut[MN], now;
int bit[2][MN];
vector< int > ke[MN];

void dfs(int u, int fu) {
    getIn[u] = ++now;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        h[v] = h[u] + 1;
        dfs(v, u);
    }
    getOut[u] = ++now;
}

#define _(X) ((X) & (-(X)))
void update(int t, int u, int val) {
    while (u <= now) {
        bit[t][u] += val;
        u += _(u);
    }
}

int get(int t, int u) {
    int res = 0;
    while (u > 0) {
        res += bit[t][u];
        u -= _(u);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> q) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n) cin >> a[i];
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        h[1] = 1;
        now = 0;
        dfs(1, -1);
        // PR(getIn, n);
        // PR(getOut, n);
        // PR(h, n);

        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int x, val; cin >> x >> val;
                update(h[x] & 1, getIn[x], val);
                update(h[x] & 1, getOut[x], -val);

                update(1 - (h[x] & 1), getIn[x], -val);
                update(1 - (h[x] & 1), getOut[x], val);
            }
            else {
                int x; cin >> x;
                cout << get(h[x] & 1, getIn[x]) + a[x] << "\n";
            }
        }
    }
    return 0;
}

