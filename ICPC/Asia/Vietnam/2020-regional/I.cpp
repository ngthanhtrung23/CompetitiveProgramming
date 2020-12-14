#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

const int INF = 1e18 + 11;
vector<int> dijkstra(int n, vector< vector< pair<int,int> > > adj, int start) {
    vector<int> d(n, INF);
    d[start] = 0;

    set< pair<int,int> > q;
    q.insert({0, start});

    while (!q.empty()) {
        const auto [cur_dist, u] = *q.begin();
        q.erase(q.begin());

        if (d[u] != cur_dist) continue;

        for (const auto [v, c] : adj[u]) {
            if (d[v] > d[u] + c) {
                d[v] = d[u] + c;
                q.insert({d[v], v});
            }
        }
    }

    return d;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n, m;
    while (cin >> n >> m && n) {
        int start[2], target[2];
        REP(t,2) {
            cin >> start[t] >> target[t];
            --start[t];
            --target[t];
        }

        vector<vector< pair<int,int > > > adj(n);
        vector< tuple<int, int, int> > edges;
        REP(i,m) {
            int u, v, c; cin >> u >> v >> c;
            --u;
            --v;

            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
            edges.push_back({u, v, c});
            edges.push_back({v, u, c});
        }

        vector<int> d_start[2];
        vector<int> d_target[2];

        REP(t,2) {
            d_start[t] = dijkstra(n, adj, start[t]);
            d_target[t] = dijkstra(n, adj, target[t]);
        }

        int res = 0;

        // is u on shortest path of t?
        auto onShortestPath = [&] (int t, int u) {
            return d_start[t][u] + d_target[t][u] == d_start[t][target[t]];
        };

        // meet at vertex
        REP(i,n) {
            // i on shortest path start[0] -> target[0]
            if (!onShortestPath(0, i)) continue;

            // i on shortest path start[1] -> target[1]
            if (!onShortestPath(1, i)) continue;

            // can meet at i
            if (d_start[0][i] != d_start[1][i]) continue;

            ++res;
        }

        // meet on edge (same direction)
        for (const auto& [u, v, c] : edges) {
            // [u, v] is on shortest path start[0] -> target[0]
            if (d_start[0][u] + c + d_target[0][v] != d_start[0][target[0]]) continue;

            // [u, v] is on shortest path start[1] -> target[1]
            if (d_start[1][u] + c + d_target[1][v] != d_start[1][target[1]]) continue;

            // can meet at u
            if (d_start[0][u] != d_start[1][u]) continue;

            res += 1e9 + 11;
        }

        // meet on edge (different direction)
        for (const auto& [u, v, c] : edges) {
            // [u, v] is on shortest path start[0] -> target[0]
            if (d_start[0][u] + c + d_target[0][v] != d_start[0][target[0]]) continue;
            
            // [v, u] is on shortest path start[1] -> target[1]
            if (d_start[1][v] + c + d_target[1][u] != d_start[1][target[1]]) continue;

            int from_0 = d_start[0][u] - c;
            int to_0 = d_start[0][u] + c;

            // can meet?
            if (d_start[1][v] > from_0 && d_start[1][v] < to_0) {
                res += 1;
            }
        }

        // 0 arrive at target[0] first, wait there
        if (d_start[0][target[0]] < d_start[1][target[0]] && onShortestPath(1, target[0])) {
            res += 1;
        }
        // 1 arrive at target[1] first, wait there
        if (d_start[1][target[1]] < d_start[0][target[1]] && onShortestPath(0, target[1])) {
            res += 1;
        }

        cout << (res > 1000000000 ? -1 : res) << endl;
    }
    return 0;
}

