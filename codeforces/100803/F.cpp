#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 511;
const int MM = 50111;

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
} dsu;

int n, m;
vector< pair<int,int> > ke[MN];
int good[MN][MN], cost[MN][MN];

struct Edge {
    int u, v, c;

    void read() {
        scanf("%d%d%d", &u, &v, &c);
    }
} edges[MM];

bool operator < (const Edge& a, const Edge& b) {
    return a.c < b.c;
}

int tr[MN];
void dfs(int u) {
    for(auto p : ke[u]) {
        int v = p.first;
        if (tr[v] >= 0) continue;

        tr[v] = u;
        dfs(v);
    }
}
void go(int u, int v, int c) {
    memset(tr, -1, sizeof tr);
    dfs(u);

    int x = v;
    while (x != u) {
        int y = tr[x];
        if (cost[y][x] >= c) {
            good[x][y] = good[y][x] = -1;
        }
        x = y;
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) ke[i].clear();
        memset(good, 0, sizeof good);
        dsu.init(n);

        FOR(i,1,m) edges[i].read();

        sort(edges+1, edges+m+1);
        FOR(i,1,m) {
            int u = edges[i].u, v = edges[i].v, c = edges[i].c;
            if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

            good[u][v] = good[v][u] = true;
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
            dsu.merge(u, v);

            cost[u][v] = cost[v][u] = edges[i].c;
        }

        FOR(i,1,m) {
            int u = edges[i].u, v = edges[i].v, c = edges[i].c;
            if (good[u][v]) continue;

            go(u, v, c);
        }

        int sum = 0, cnt = 0;
        FOR(i,1,m) {
            int u = edges[i].u, v = edges[i].v;
            if (good[u][v] == 1) {
                ++cnt;
                sum += edges[i].c;
            }
        }
        printf("%d %d\n", cnt, sum);
    }
}
