#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 10111;
struct Edge {
    int u, v, c;
};
bool operator < (const Edge& a, const Edge& b) {
    return a.c < b.c;
}

int lab[MN];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void join(int u, int v) {
    u = getRoot(u);
    v = getRoot(v);

    lab[u] = v;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n, m;
    while (cin >> n >> m) {
        vector<Edge> edges(m);
        for (auto& e : edges) {
            cin >> e.u >> e.v >> e.c;
        }
        sort(edges.begin(), edges.end());

        for (int i = 1; i <= n; i++) lab[i] = -1;

        int res = 0;
        for (auto e : edges) {
            if (getRoot(e.u) != getRoot(e.v)) {
                res = max(res, e.c);
                join(e.u, e.v);
            }
        }
        cout << res << endl;
    }
    return 0;
}
