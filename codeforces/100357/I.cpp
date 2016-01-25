
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

const int INF = 1000000000;
 
struct Edge {
    int a, b, cap, flow;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int n) : n(n), d(n), ptr(n), q(n), g(n) {
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

int n, k;
int var[333];
vector<int> expr[333];
int sign[333][333];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("sat.in", "r", stdin);
    freopen("sat.out", "w", stdout);
    while (cin >> n >> k) {
        MaxFlow flow(n + k + 3);

        int source = 0;
        int bad = n + k + 1;
        int sink = n + k + 2;

        FOR(i,1,n) flow.addEdge(source, i, 1);
        FOR(i,n+1,n+k) flow.addEdge(i, sink, 1);
        flow.addEdge(bad, sink, n - k);

        FOR(i,1,n) var[i] = 0;
        memset(sign, 0, sizeof sign);
        FOR(i,1,k) {
            expr[i].clear();
            int t; cin >> t;
            while (t--) {
                int u; cin >> u;
                expr[i].push_back(u);

                if (u < 0) sign[i][-u] = -1;
                else sign[i][u] = 1;

                u = abs(u);
                var[u]++;

                flow.addEdge(u, n+i, 1);
            }
        }
        FOR(i,1,n) if (var[i] < 2) flow.addEdge(i, bad, 1);

        int t = flow.getMaxFlow(source, sink);
        if (t == n) {
            cout << "YES" << endl;
            FOR(i,1,n) {
                for(auto eid : flow.g[i]) {
                    int fl = flow.e[eid].flow;
                    if (fl == 1) {
                        int x = flow.e[eid].b;
                        if (x == bad) {
                            bool ok = false;
                            FOR(j,1,k) {
                                if (sign[j][i] == 1) {
                                    cout << "0 ";
                                    ok = true;
                                    break;
                                }
                                if (sign[j][i] == -1) {
                                    cout << "1 ";
                                    ok = true;
                                    break;
                                }
                            }
                            if (!ok) cout << "0 ";
                        }
                        else {
                            if (sign[x - n][i] == -1) cout << "0 ";
                            else cout << "1 ";
                        }
                    }
                }
            }
            cout << endl;
        }
        else cout << "NO" << endl;
    }
}
