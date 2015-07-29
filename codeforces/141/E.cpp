
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 100111;
struct DSU {
    int lab[MN];
    void init(int n) {
        REP(i,n+1) lab[i] = -1;
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};
int n, m;
pair< pair<int,int>, char > edges[MN];
bool chosen[MN];

void solve() {
    memset(chosen, false, sizeof chosen);
    DSU dsu; dsu.init(n);

    if ((n-1) % 2) {
        cout << -1 << endl;
        return ;
    }

    int need = (n-1) / 2, addedS = 0;
    FOR(i,1,m) if (edges[i].second == 'S') {
        int u = edges[i].first.first, v = edges[i].first.second;

        if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

        ++addedS;
        dsu.merge(u, v);
    }
    if (addedS < need) {
        cout << -1 << endl;
        return ;
    }

    FOR(i,1,m) if (edges[i].second == 'M') {
        int u = edges[i].first.first, v = edges[i].first.second;

        if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

        dsu.merge(u, v);
        chosen[i] = true;
    }

    FOR(i,2,n) if (dsu.getRoot(i) != dsu.getRoot(1)) {
        cout << -1 << endl;
        return ;
    }

    dsu.init(n);
    int addedM = 0;
    FOR(i,1,m) if (chosen[i]) {
        int u = edges[i].first.first, v = edges[i].first.second;
        dsu.merge(u, v);
        ++addedM;
    }

    FOR(i,1,m) if (edges[i].second == 'M') {
        if (addedM == need) break;

        int u = edges[i].first.first, v = edges[i].first.second;

        if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

        dsu.merge(u, v);
        ++addedM;
        chosen[i] = true;
    }
    if (addedM < need) {
        cout << -1 << endl;
        return ;
    }

    FOR(i,1,m) if (edges[i].second == 'S') {
        int u = edges[i].first.first, v = edges[i].first.second;
        if (dsu.getRoot(u) == dsu.getRoot(v)) continue;
        dsu.merge(u, v);
        chosen[i] = true;
    }

    cout << n-1 << endl;
    FOR(i,1,m) if (chosen[i]) cout << i << ' '; cout << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,m) cin >> edges[i].first.first >> edges[i].first.second >> edges[i].second;

        solve();
    }
}

