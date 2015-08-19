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

const int INF = 1000000000;
 
struct Edge {
    int a, b, cap, flow;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int n) : n(n), d(n), ptr(n), g(n), q(n) {
        e.clear();
        REP(i,n) {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int a, int b, int cap) {
        Edge e1 = { a, b, cap, 0 };
        Edge e2 = { b, a, 0, 0 };
        g[a].push_back( (int) e.size() );
        e.push_back(e1);
        g[b].push_back( (int) e.size() );
        e.push_back(e2);
    }
    int getMaxFlow(int _s, int _t) {
        s = _s; t = _t;
        int flow = 0;
        for (;;) {
            if (!bfs()) break;
            REP(i,n) ptr[i] = 0;
            while (int pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }

private:
    bool bfs() {
        int qh = 0, qt = 0;
        q[qt++] = s;
        REP(i,n) d[i] = -1;
        d[s] = 0;

        while (qh < qt && d[t] == -1) {
            int v = q[qh++];
            REP(i,g[v].size()) {
                int id = g[v][i], to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs (int v, int flow) {
        if (!flow) return 0;
        if (v == t) return flow;
        for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1) continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
};

const int MN = 211;

int high[MN][MN], low[MN][MN], id[MN][MN];
int res[MN * MN];
int M[MN];

int main() {
    ios :: sync_with_stdio(false);
    freopen("cooling.in", "r", stdin);
    freopen("cooling.out", "w", stdout);
    int n, m;
    while (cin >> n >> m) {
        memset(high, -1, sizeof high);
        memset(low, -1, sizeof low);
        memset(M, 0, sizeof M);

        MaxFlow flow(n+2);
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            cin >> low[u][v];
            cin >> high[u][v];
            M[v] += low[u][v];
            M[u] -= low[u][v];

            id[u][v] = id[v][u] = i;
            res[i] = low[u][v];

            flow.addEdge(u, v, high[u][v] - low[u][v]);
        }
//        PR(M, n);

        int need = 0;
        FOR(i,1,n) {
            if (M[i] > 0) {
                flow.addEdge(0, i, M[i]);
                need += M[i];
            }
            else flow.addEdge(i, n+1, -M[i]);
        }

        int has = flow.getMaxFlow(0, n+1);
        if (has < need) puts("NO");
        else {
            puts("YES");
            FOR(u,1,n) {
                for(int edge_id : flow.g[u]) {
                    auto e = flow.e[edge_id];
                    if (e.flow > 0) {
                        int v = e.b;
                        if (v < 1 || v > n) continue;
                        res[id[u][v]] += e.flow;
                    }
                }
            }
            FOR(i,1,m) printf("%d\n", res[i]);
        }
    }
}