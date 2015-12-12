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

const double INF = 1e10;
 
struct Edge {
    int a, b;
    double cap, flow;
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

    void addEdge(int a, int b, double cap) {
        Edge e1 = { a, b, cap, 0 };
        Edge e2 = { b, a, 0, 0 };
        g[a].push_back( (int) e.size() );
        e.push_back(e1);
        g[b].push_back( (int) e.size() );
        e.push_back(e2);
    }
    double getMaxFlow(int _s, int _t) {
        s = _s; t = _t;
        double flow = 0;
        for (;;) {
            if (!bfs()) break;
            REP(i,n) ptr[i] = 0;
            while (double pushed = dfs(s, INF))
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

    double dfs (int v, double flow) {
        if (!flow) return 0;
        if (v == t) return flow;
        for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1) continue;
            double pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
};
int n, m, eu[10111], ev[10111];
bool mark[10111], visited[10111];

bool check(double val) {
    MaxFlow flow(n+m+2);
    FOR(i,1,m) flow.addEdge(0, i, 1);
    FOR(i,m+1,m+n) flow.addEdge(i, m+n+1, val);

    FOR(i,1,m) {
        int u = m + eu[i], v = m + ev[i];
        flow.addEdge(i, u, INF);
        flow.addEdge(i, v, INF);
    }

    double mf = flow.getMaxFlow(0, m+n+1);
    return mf >= m;
}

int a[111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n;
        FOR(i,1,n) cin >> a[i];

        m = 0;
        FOR(i,1,n) FOR(j,i+1,n) if (a[i] > a[j]) {
            ++m;
            eu[m] = i;
            ev[m] = j;
        }
        double l = 0, r = 1e3, res = 1e3;
        REP(turn,50) {
            double mid = (l + r) / 2.0;
            if (check(mid)) {
                res = mid;
                r = mid;
            }
            else l = mid;
        }
        memset(mark, false, sizeof mark);
        cout << "Case #" << test << ": " << res << '\n';
    }
    return 0;
}
