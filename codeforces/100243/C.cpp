
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

const int MN = 111;
int n, m, k;
int edgeColor[MN][MN];
int idLeft[MN], idRight[MN], idLeftCol[MN][6], idRightCol[MN][6];
vector<int> ke[MN * 2];
bool visited[MN];

void init() {
    memset(edgeColor, 0, sizeof edgeColor);
    FOR(i,1,n+n) ke[i].clear();
    memset(visited, 0, sizeof visited);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("colorful.in", "r", stdin);
    freopen("colorful.out", "w", stdout);
    while (cin >> n >> m >> k) {
        init();
        FOR(i,1,m) {
            int u, v, c; cin >> u >> v >> c;
            v = -v;
            edgeColor[u][v] = c;
        }
        int cur = 0;
        int source = cur++;
        FOR(i,1,n) idLeft[i] = cur++;
        FOR(i,1,n) FOR(col,1,k) {
            idLeftCol[i][col] = cur++;
        }
        FOR(i,1,n) FOR(col,1,k) {
            idRightCol[i][col] = cur++;
        }
        FOR(i,1,n) idRight[i] = cur++;
        int sink = cur++;

        MaxFlow flow(cur);
        FOR(i,1,n) flow.addEdge(source, idLeft[i], 2);
        FOR(i,1,n) FOR(col,1,k) flow.addEdge(idLeft[i], idLeftCol[i][col], 1);
        FOR(i,1,n) FOR(col,1,k) flow.addEdge(idRightCol[i][col], idRight[i], 1);

        FOR(i,1,n) FOR(j,1,n) if (edgeColor[i][j]) {
            int c = edgeColor[i][j];
            flow.addEdge(idLeftCol[i][c], idRightCol[j][c], 1);
        }
        FOR(i,1,n) flow.addEdge(idRight[i], sink, 2);

        int fl = flow.getMaxFlow(source, sink);
        if (fl == n * 2) {
            cout << "YES" << endl;

            FOR(i,1,n) FOR(c,1,k) {
                int u = idLeftCol[i][c];
                for(auto eid : flow.g[u]) {
                    auto e = flow.e[eid];
                    if (e.flow == 1) {
                        int v = e.b;
                        int j = -1;
                        FOR(x,1,n) if (idRightCol[x][c] == v) {
                            j = x;
                            ke[i].push_back(j+n);
                            ke[j+n].push_back(i);
                            break;
                        }
                    }
                }
            }
            vector< vector<int> > all;
            FOR(i,1,n) if (!visited[i]) {
                vector<int> cur;
                cur.push_back(i);
                visited[i] = true;

                int u = i;
                while (true) {
                    bool found = false;
                    for(int v : ke[u]) {
                        if (!visited[v]) {
                            visited[v] = true;
                            cur.push_back(v);
                            u = v;
                            found = true;
                            break;
                        }
                    }
                    if (!found) break;
                }

                all.push_back(cur);
            }
            cout << SZ(all) << '\n';
            for(auto p : all) {
                cout << SZ(p);
                for(int x : p) {
                    cout << ' ' << (x <= n ? x : -(x - n));
                }
                cout << '\n';
            }
        }
        else cout << "NO" << endl;
    }
}
