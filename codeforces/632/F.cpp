
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 2511;
int n, a[MN][MN];

int lab[MN];
struct DSU {
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

pair< int, pair<int,int> > edges[MN * MN];
vector< pair<int,int> > ke[MN];
int f[MN];

void bfs(int start) {
    queue<int> qu;
    qu.push(start);
    memset(f, -1, sizeof f);
    f[start] = 0;

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for(auto e : ke[u]) {
            int v = e.first;
            int cost = e.second;

            if (f[v] >= 0) continue;

            f[v] = max(f[u], cost);
            qu.push(v);
        }
    }
}

bool check() {
    // basic check: a[i][i] = 0 and a[i][j] = a[j][i]
    FOR(i,1,n) if (a[i][i]) return false;
    FOR(i,1,n) FOR(j,i+1,n) if (a[i][j] != a[j][i]) return false;

    // build MST
    DSU dsu; dsu.init(n + 10);
    int m = 0;
    FOR(i,1,n) FOR(j,i+1,n) edges[++m] = make_pair(a[i][j], make_pair(i, j));
    sort(edges+1, edges+m+1);

    FOR(i,1,m) {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int cost = edges[i].first;

        if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

        dsu.merge(u, v);
        ke[u].push_back(make_pair(v, cost));
        ke[v].push_back(make_pair(u, cost));
    }

    FOR(u,1,n) {
        bfs(u);
        FOR(v,1,n) if (a[u][v] != f[v]) return false;
    }
    return true;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%lld", &n) == 1) {
        FOR(i,1,n) FOR(j,1,n) scanf("%lld", &a[i][j]);
        cout << (check() ? "MAGIC" : "NOT MAGIC") << endl;
    }
}
