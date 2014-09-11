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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 300111;
int n, m, q, lab[MN];
vector<int> ke[MN];
bool visited[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
    memset(lab, -1, sizeof lab);
    memset(visited, false, sizeof visited);
}

int diam[MN];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    u = getRoot(u);
    v = getRoot(v);
    if (u == v) return ;
    int x = lab[u] + lab[v];
    int newDiam = max(max(diam[u], diam[v]), (diam[u] + 1) / 2 + (diam[v] + 1) / 2 + 1);
    if (lab[u] < lab[v]) {
        lab[u] = x;
        lab[v] = u;
    } else {
        lab[v] = x;
        lab[u] = v;
    }
    diam[u] = diam[v] = newDiam;
}

int ln[MN], farthest[MN];

void dfs(int u, int fu) {
    ln[u] = 0;
    farthest[u] = u;
    visited[u] = true;

    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs(v, u);
        if (ln[v] + 1 > ln[u]) {
            ln[u] = ln[v] + 1;
            farthest[u] = farthest[v];
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> q) {
        init();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
            merge(u, v);
        }
        memset(diam, 0, sizeof diam);
        FOR(i,1,n)
            if (!visited[i]) {
                dfs(i, -1);
                int u = farthest[i];
                dfs(u, -1);
                diam[getRoot(u)] = ln[u];
            }
        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int u; cin >> u;
                u = getRoot(u);
                cout << diam[u] << endl;
            } else {
                int u, v;
                cin >> u >> v;
                merge(u, v);
            }
        }
    }
    return 0;
}

