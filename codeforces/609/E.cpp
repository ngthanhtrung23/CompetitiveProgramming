
#include <bits/stdc++.h>
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

const int MN = 200111;
int n, m, lab[MN];
struct Edge {
    int u, v, c, id;

    void read() {
        scanf("%d%d%d", &u, &v, &c);
    }
} edges[MN];
ll res[MN];

bool operator < (const Edge& a, const Edge& b) {
    return a.c < b.c;
}

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}
void merge(int u, int v) {
    u = getRoot(u); v = getRoot(v);
    lab[u] += lab[v];
    lab[v] = u;
}

vector< pair<int,int> > ke[MN];
int h[MN], father[20][MN], ln[20][MN];

void dfs(int u, int fu) {
    for(auto e : ke[u]) {
        int v = e.first;
        if (v == fu) continue;

        h[v] = h[u] + 1;
        father[0][v] = u;
        ln[0][v] = e.second;
        dfs(v, u);
    }
}

void initLCA() {
    FOR(i,1,19) {
        FOR(u,1,n) {
            int x = father[i-1][u];
            father[i][u] = father[i-1][x];
            ln[i][u] = max(ln[i-1][u], ln[i-1][x]);
        }
    }
}

int getMax(int u, int v) {
    int res = 0;
    if (u == v) return res;

    if (h[u] > h[v]) swap(u, v);
    if (h[u] < h[v]) {
        FORD(i,19,0) {
            int x = father[i][v];
            if (h[x] >= h[u]) {
                res = max(res, ln[i][v]);
                v = x;
            }
        }
    }
    if (u == v) return res;

    FORD(i,19,0) if (father[i][u] != father[i][v]) {
        res = max(res, ln[i][u]);
        res = max(res, ln[i][v]);
        u = father[i][u];
        v = father[i][v];
    }
    res = max(res, ln[0][u]);
    res = max(res, ln[0][v]);

    return res;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,m) {
            edges[i].read();
            edges[i].id = i;
        }
        sort(edges+1, edges+m+1);
        memset(lab, -1, sizeof lab);

        set< pair<int,int> > good;
        ll sum = 0;

        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u = edges[i].u, v = edges[i].v;
            if (getRoot(u) == getRoot(v)) continue;

            merge(u, v);
            good.insert(make_pair(u, v));
            good.insert(make_pair(v, u));

            sum += edges[i].c;

            ke[u].push_back(make_pair(v, edges[i].c));
            ke[v].push_back(make_pair(u, edges[i].c));
        }

        h[1] = 1;
        father[0][1] = 0;
        dfs(1, -1);
        initLCA();

        FOR(i,1,m) {
            int u = edges[i].u, v = edges[i].v;
            int id = edges[i].id;
            if (good.count(make_pair(u, v))) res[id] = sum;
            else res[id] = sum - getMax(u, v) + edges[i].c;
        }

        FOR(i,1,m) printf("%lld\n", res[i]);
    }
}
