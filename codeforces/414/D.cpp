#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

int n, k, p, maxLevel, h[MN];
vector<int> ke[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
    maxLevel = 0;
}

void dfs(int u, int fu, int level) {
    maxLevel = max(maxLevel, level);
    h[u] = level;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        dfs(v, u, level + 1);
    }
}

multiset<int> all, used;
int decAll;

int valTop(const multiset<int> &all) {
    return *all.begin() - decAll;
}

void print(const multiset<int> &all) {
    for(__typeof(all.begin()) it = all.begin(); it != all.end(); ++it)
        cout << (*it) - decAll << ' ';
    cout << endl;
}

void solve() {
    decAll = 0;
    all.clear(); used.clear();
    FOR(i,2,n) all.insert(maxLevel - h[i]);
    // print(all);

    int res = 0;
    FORD(i,maxLevel,1) {
        while (!all.empty() && p >= valTop(all)) {
            p -= valTop(all);
            used.insert(*all.begin());
            all.erase(all.begin());
        }

        // DEBUG(i);
        // print(used);

        res = max(res, (int) used.size());

        while (!used.empty() && valTop(used) == 0) {
            used.erase(used.begin());
        }
        ++decAll;
        p += used.size();
    }
    res = min(res, k);
    cout << res << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> k >> p) {
        init();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        dfs(1, -1, 0);
        solve();
    }
    return 0;
}
