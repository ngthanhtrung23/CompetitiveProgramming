#include "bits/stdc++.h"
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
using namespace std;

struct Edge {
    int u, v, c;
};

const int MN = 211;
struct DSU {
    int lab[MN];
    void init(int n) {
        REP(i,n+2) lab[i] = -1;
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
} dsu;

int res[MN][MN], F[MN][MN];

void solve() {
    // input
    vector<Edge> edges;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int f; cin >> f;
            F[i][j] = f;
            edges.push_back({i, j, f});
        }
    }

    // gomory-hu tree of output graph == max spanning tree of input graph
    sort(edges.begin(), edges.end(), [](const Edge&a, const Edge&b) {
        return a.c > b.c;
    });

    memset(res, 0, sizeof res);
    dsu.init(n);
    vector< vector<pair<int, int>> > gomory(n);
    for (auto [u, v, c] : edges) {
        if (dsu.merge(u, v)) {
            res[u][v] = res[v][u] = c;
            gomory[u].push_back({v, c});
            gomory[v].push_back({u, c});
        }
    }

    // on Gomory-hu tree, min-cut(i, j) == min edge in path i -> j
    // we need to verify input(i, j)
    const int INF = 1000111000;
    for (int i = 0; i < n; i++) {
        vector<int> min_edges(n, INF);

        queue<int> qu;
        qu.push(i);
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();

            for (auto [v, c] : gomory[u]) {
                if (min_edges[v] == INF) {
                    min_edges[v] = min(min_edges[u], c);
                    qu.push(v);
                }
            }
        }
        min_edges[i] = 0;

        for (int j = 0; j < n; j++) {
            if (F[i][j] != min_edges[j]) {
                cout << "NO\n";
                return;
            }
        }
    }

    // output
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << ' ';
        }
        cout << '\n';
    }
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int ntest; cin >> ntest;
    for (int test = 1; test <= ntest; test++) {
        cout << "Case #" << test << ": ";
        solve();
    }

    return 0;
}
