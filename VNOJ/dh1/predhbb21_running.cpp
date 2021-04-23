#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 100111;
map< pair<int,int>, int > edgeToCost;
vector<int> ke[MN];
int visited[MN];
const int INF = 1000111000;

int getPathCost(const vector<int> path, int i1, int i2) {
    int s_to_t = INF;
    for (int i = i1; i < i2; i++) {
        int x = path[i];   // sz(path) - 3
        int y = path[i+1]; // sz(path) - 2
        s_to_t = min(s_to_t, edgeToCost[{x, y}]);
    }
    return s_to_t;
}

int32_t main() {
    ios::sync_with_stdio(0);

    int n, start, target;
    cin >> n >> start >> target;
    // init
    for (int i = 1; i <= n; i++) {
        ke[i].clear();
    }
    edgeToCost.clear();

    // input
    for (int i = 1; i < n; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        ke[u].push_back(v);
        ke[v].push_back(u);

        edgeToCost[{u, v}] = cost;
        edgeToCost[{v, u}] = cost;
    }

    // find path
    memset(visited, 0, sizeof visited);
    queue<int> qu; qu.push(start);
    visited[start] = start;
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for (int v : ke[u]) {
            if (!visited[v]) {
                visited[v] = u;
                qu.push(v);
            }
        }
    }
    assert(visited[target]);

    vector<int> path;
    {
        int v = target;
        while (v != start) {
            path.push_back(v);
            v = visited[v];
        }
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    assert(path[0] == start);
    
    // cout << "path = "; for (int x : path) cout << x << ' '; cout << endl;

    int res = -1;
    // case green
    if (SZ(path) >= 4) {
        // connect path[1] - path[2]
        int cur = min(
            edgeToCost[{path[0], path[1]}],
            edgeToCost[{path[SZ(path) - 2], path[SZ(path) - 1]}]
        );
        res = max(res, cur);
    }

    int best_weight_u = -1;
    int best_u = -1;
    for (int u : ke[start]) {
        if (u == path[1]) continue;

        int w = edgeToCost[{start, u}];
        if (w > best_weight_u) {
            best_weight_u = w;
            best_u = u;
        }
    }

    int best_weight_v = -1;
    int best_v = -1;
    for (int v : ke[target]) {
        if (v == path[SZ(path) - 2]) continue;

        int w = edgeToCost[{v, target}];
        if (w > best_weight_v) {
            best_weight_v = w;
            best_v = v;
        }
    }

    // case red
    if (best_u != -1) {
        int u = best_u;
        assert(u != path[1]);

        int s_to_t = getPathCost(path, 0, SZ(path) - 2);

        int cur = min(
            s_to_t + edgeToCost[{start, u}],
            edgeToCost[{path[SZ(path) - 2], target}]);

        res = max(res, cur);
    }

    // case blue
    if (best_v != -1) {
        int v = best_v;
        assert(v != path[SZ(path) - 2]);

        int s_to_t = getPathCost(path, 1, SZ(path) - 1);
        int cur = min(
                s_to_t + edgeToCost[{v, target}],
                edgeToCost[{start, path[1]}]);
        res = max(res, cur);
    }

    // case purple
    if (best_u != -1 && best_v != -1) {
        int s_to_t = getPathCost(path, 0, SZ(path) - 1);
        res = max(res, s_to_t + min(best_weight_v, best_weight_u));
    }
    
    res = max(res, getPathCost(path, 0, SZ(path) - 1));

    cout << res << endl;
    return 0;
}
