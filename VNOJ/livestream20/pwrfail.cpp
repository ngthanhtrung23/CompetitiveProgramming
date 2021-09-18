#include "bits/stdc++.h"
using namespace std;

#define int long long
#define double long double
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

struct Point {
    double x, y;
};

double sqr(double x) {
    return x*x;
}
double dist(const Point& a, const Point& b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

const int MN = 1011;
Point pos[MN];
double d[MN];

vector<int> edges0[MN];

int cmp(double x, double y) {
    if (abs(x - y) < 1e-5) return 0;
    if (x < y) return -1;
    return 1;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // input
    int n, w; cin >> n >> w;
    double M; cin >> M;
    for (int i = 1; i <= n; i++) {
        cin >> pos[i].x >> pos[i].y;
    }
    while (w--) {
        int u, v; cin >> u >> v;
        edges0[u].push_back(v);
        edges0[v].push_back(u);
    }
    // dijkstra
    for (int i = 1; i <= n; i++) {
        d[i] = 1e100;
    }
    d[1] = 0;
    set< pair<double, int> > all;
    all.insert({0.0, 1});
    while (!all.empty()) {
        auto [du, u] = *all.begin();
        all.erase(all.begin());

        if (cmp(du, d[u])) continue;
        if (u == n) {
            cout << (int) (du * 1000 + 1e-5) << endl;
            return 0;
        }

        // for 0 - edges
        for (auto v : edges0[u]) {
            if (d[v] > d[u]) {
                d[v] = d[u];
                all.insert({d[v], v});
            }
        }

        // for each other vertices
        for (int v = 1; v <= n; v++) {
            double len = dist(pos[u], pos[v]);
            if (cmp(len, M) > 0) {
                continue;
            }

            if (d[v] > d[u] + len) {
                d[v] = d[u] + len;
                all.insert({d[v], v});
            }
        }
    }
    cout << -1 << endl;
    return 0;
}

