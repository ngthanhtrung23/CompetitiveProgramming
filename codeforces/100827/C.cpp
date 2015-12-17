
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
const int INF = 1000000;
 
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

int a[15][15][15], id[15][15][15];

const int di[6] = {-1,0,0,0,0,1};
const int dj[6] = {0,-1,1,0,0,0};
const int dk[6] = {0,0,0,-1,1,0};

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        memset(a, 0, sizeof a);
        memset(id, 0, sizeof id);

        FOR(i,1,n) {
            int x, y, z;
            cin >> x >> y >> z;
            ++x; ++y; ++z;
            a[x][y][z] = 1;
        }

        int s = 0, cur = 0;
        FOR(i,0,11) FOR(j,0,11) FOR(k,0,11) id[i][j][k] = ++cur;
        int t = ++cur;

        MaxFlow flow(t+1);
        FOR(i,0,11) FOR(j,0,11) FOR(k,0,11) {
            if (a[i][j][k]) flow.addEdge(s, id[i][j][k], INF);
            if (i == 0 || i == 11 || j == 0 || j == 11 || k == 0 || k == 11)
                flow.addEdge(id[i][j][k], t, INF);

            REP(dir,6) {
                int ii = i + di[dir], jj = j + dj[dir], kk = k + dk[dir];
                if (ii < 0 || ii > 11) continue;
                if (jj < 0 || jj > 11) continue;
                if (kk < 0 || kk > 11) continue;
                flow.addEdge(id[i][j][k], id[ii][jj][kk], 1);
            }
        }
        cout << flow.getMaxFlow(s, t) << endl;
    }
}
