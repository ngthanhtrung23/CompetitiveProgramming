
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

const int MN = 200111;

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
pair<int, pair<int,int> > edges[MN * 2];
vector<int> ke[MN];
set<int> buses[MN];

int dfs(int u, int fu) {
    vector<int> cur;
    cur.push_back(u);
    for(int v : ke[u]) if (v != fu) {
        int b = dfs(v, u);
        printf("Drive %d %d %d\n", b, v, u);
        cur.push_back(b);
    }

    int best_bus = cur[0];
    for(int x : cur) if (buses[x].size() > buses[best_bus].size()) {
        best_bus = x;
    }

    for(int x : cur) if (x != best_bus) {
        for(int dr : buses[x]) {
            printf("Move %d %d %d\n", dr, x, best_bus);
        }
        buses[best_bus].insert(buses[x].begin(), buses[x].end());
    }
    return best_bus;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n) {
            buses[i].clear();
            buses[i].insert(i);
        }
        FOR(i,1,m) scanf("%d%d%d", &edges[i].second.first, &edges[i].second.second, &edges[i].first);
        sort(edges+1, edges+m+1);

        DSU dsu; dsu.init(n);
        ll res = 0;
        FOR(i,1,m) {
            int u = edges[i].second.first, v = edges[i].second.second;
            if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

            res += edges[i].first;
            dsu.merge(u, v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        cout << res << endl;
        dfs(1, -1);
        puts("Done");
    }
}
