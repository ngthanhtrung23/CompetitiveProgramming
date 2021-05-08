#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 200111;
struct Edge {
    int to;
    list<Edge>::iterator rev;

    Edge(int _to) :to(_to) {}
};

list<Edge> adj[MN];
vector<int> path; // our result

void find_path(int v) {
    while(adj[v].size() > 0) {
        int vn = adj[v].front().to;
        adj[vn].erase(adj[v].front().rev);
        adj[v].pop_front();
        find_path(vn);
    }
    path.push_back(v);
}

void add_edge(int a, int b) {
    adj[a].push_front(Edge(b));
    auto ita = adj[a].begin();
    adj[b].push_front(Edge(a));
    auto itb = adj[b].begin();
    ita->rev = itb;
    itb->rev = ita;
}

int n, m, k;
int deg[MN];
int teleport[MN];
int visited[MN];

void dfs(int u) {
    visited[u] = 1;

    if (teleport[u] && !visited[teleport[u]]) {
        dfs(teleport[u]);
    }

    for (auto e : adj[u]) {
        int v = e.to;
        if (!visited[v]) {
            dfs(v);
        }
    }
}

bool can() {
    memset(visited, 0, sizeof visited);

    // check teleport: diff <= 2
    int diff_1 = 0;
    int diff_2 = 0;

    for (int i = 1; i <= n; i++) {
        int j = teleport[i];
        if (!j) continue;

        int diff = abs(deg[i] - deg[j]);
        if (diff > 2) return false;

        if (i < j) {
            if (diff == 1) diff_1++;
            if (diff == 2) diff_2++;
        }
    }
    if (diff_2 > 1) return false;

    // odd degree
    int odd = 0;
    for (int i = 1; i <= n; i++) {
        if (teleport[i] == 0) {
            odd += deg[i] % 2;
        }
    }

    if (odd + diff_1 == 1) return false;
    if (odd + diff_1 > 2) return false;
    if (diff_2 == 1 && odd + diff_1 > 0) return false;

    for (int u = 1; u <= n; u++) {
        if (deg[u] > 0 || teleport[u] > 0) {
            dfs(u);
            break;
        }
    }

    for (int u = 1; u <= n; u++) {
        if (deg[u] > 0 || teleport[u] > 0) {
            if (!visited[u]) return false;
        }
    }

    return true;
}

void init() {
    memset(deg, 0, sizeof deg);
    memset(teleport, 0, sizeof teleport);
}


int32_t main() {
    ios::sync_with_stdio(0);
    while (cin >> n >> m >> k && (n || m || k)) {
        init();

        for (int i = 1; i <= m; i++) {
            int u, v; cin >> u >> v;
            deg[u]++;
            deg[v]++;

            add_edge(u, v);
        }

        for (int i = 1; i <= k; i++) {
            int u, v; cin >> u >> v;
            teleport[u] = v;
            teleport[v] = u;
        }

        if (!can()) {
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
    }
    return 0;
}
