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
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int INF = 1000111000111000111LL;
 
struct Edge {
    int a, b, cap, flow, id;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int _n) : n(_n), d(_n), ptr(_n), q(_n), g(_n) {
        e.clear();
        REP(i,n) {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int a, int b, int cap, int id) {
        Edge e1 = { a, b, cap, 0, id };
        Edge e2 = { b, a, 0, 0, id };
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

    vector<int> trace() {
        bfs();
        vector<int> res;
        for(auto edge : e) {
            if (d[edge.a] >= 0 && d[edge.b] < 0 && edge.cap > 0) {
                res.push_back(edge.id);
            }
        }
        return res;
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

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int nRow, nCol; cin >> nRow >> nCol;
        vector<int> rows(nRow), cols(nCol);
        for(int& x : rows) cin >> x;
        for(int& x : cols) cin >> x;

        if (std::accumulate(rows.begin(), rows.end(), 0)
                != std::accumulate(cols.begin(), cols.end(), 0)) {
            cout << "Case #" << test << ": IMPOSSIBLE" << endl;
            continue;
        }

        // row vertices: 0 -> nRow - 1
        // col vertices: nRow -> nRow + nCol - 1
        int source = nRow + nCol;
        int sink = nRow + nCol + 1;
        MaxFlow flow(sink + 1);

        // init one solution using max flow
        REP(i,nRow) flow.addEdge(source, i, rows[i], -1);
        REP(j,nCol) flow.addEdge(nRow + j, sink, cols[j], -1);
        REP(i,nRow) REP(j,nCol) flow.addEdge(i, nRow + j, 1, i*nCol + j);

        int f = flow.getMaxFlow(source, sink);
        if (f != std::accumulate(rows.begin(), rows.end(), 0)) {
            cout << "Case #" << test << ": IMPOSSIBLE" << endl;
            continue;
        }

        vector<vector<char>> a(nRow, vector<char>(nCol, '\\'));
        for (auto e : flow.e) {
            if (e.id < 0) continue;
            if (e.flow == 0) continue;

            int r = e.id / nCol;
            int c = e.id % nCol;
            a[r][c] = '/';
        }

        // flip squares until square-free
        while (true) {
            bool found = false;
            REP(i1,nRow) FOR(i2,i1+1,nRow-1)
            REP(j1,nCol) FOR(j2,j1+1,nCol-1) {
                if (a[i1][j1] == '/'
                        && a[i1][j2] == '\\'
                        && a[i2][j1] == '\\'
                        && a[i2][j2] == '/') {
                    a[i1][j1] = '\\';
                    a[i1][j2] = '/';
                    a[i2][j1] = '/';
                    a[i2][j2] = '\\';
                    found = true;
                }
            }
            if (!found) break;
        }

        cout << "Case #" << test << ": POSSIBLE" << endl;
        REP(i,nRow) REP(j,nCol) {
            cout << a[i][j];
            if (j == nCol-1) cout << '\n';
        }
    }
    return 0;
}
