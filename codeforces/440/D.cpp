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

vector< pair<int,int> > tr[411][411], savetr[411][411];
int f[411][411], savef[411][411];
int n, k, sz[411];
vector<int> ke[411];
int eu[411], ev[411], chosen[411];

void dfs(int u, int fu = -1) {
    tr[u][1].push_back(make_pair(u, 0));
    f[u][1] = ke[u].size();
    sz[u] = 1;

    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs(v, u);

        FOR(i,1,sz[u]) {
            savef[u][i] = f[u][i];
            savetr[u][i] = tr[u][i];
        }

        FOR(y,1,sz[v]) if (f[v][y] >= 0)
            FORD(x,sz[u],1) if (savef[u][x] >= 0)
            if (x + y <= k) {
                int cur = savef[u][x] - 2 + f[v][y];
                if (f[u][x+y] < 0 || f[u][x+y] > cur) {
                    tr[u][x+y] = savetr[u][x];
                    tr[u][x+y].push_back(make_pair(v, y));
                    f[u][x+y] = cur;
                }
            }
        sz[u] += sz[v];
    }
}

void trace(int u, int k) {
    // cout << u << ' ' << k << endl;
    chosen[u] = 1;
    REP(i,tr[u][k].size()) {
        trace(tr[u][k][i].first, tr[u][k][i].second);
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n) FOR(j,0,400) tr[i][j].clear();
        memset(f, -1, sizeof f);
        memset(chosen, 0, sizeof chosen);

        FOR(i,1,n-1) {
            cin >> eu[i] >> ev[i];
            ke[eu[i]].push_back(ev[i]);
            ke[ev[i]].push_back(eu[i]);
        }
        dfs(1);

        int best = 1000111000, save = 1;
        FOR(i,1,n) if (f[i][k] >= 0 && f[i][k] < best) {
            best = f[i][k];
            save = i;
        }
        trace(save, k);
        // PR(chosen, n);
        // DEBUG(save);
        // DEBUG(best);

        vector<int> res;
        FOR(i,1,n-1)
            if (chosen[eu[i]] ^ chosen[ev[i]]) {
                res.push_back(i);
            }
        cout << res.size() << endl;
        REP(i,res.size()) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}
