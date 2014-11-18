#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

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
int n, m, eu[1011], ev[1011];
bool mark[1011], visited[1011];

bool check(double val, bool trace = false) {
    MaxFlow flow(n+m+2);
    FOR(i,1,m) flow.addEdge(0, i, 1);
    FOR(i,m+1,m+n) flow.addEdge(i, m+n+1, val);

    FOR(i,1,m) {
        int u = m + eu[i], v = m + ev[i];
        flow.addEdge(i, u, INF);
        flow.addEdge(i, v, INF);
    }

    // DEBUG(flow.getMaxFlow(0, m+n+1));
    double mf = flow.getMaxFlow(0, m+n+1);
    if (trace) {
        memset(visited, false, sizeof visited);
        queue<int> qu;
        qu.push(0);
        visited[0] = true;
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            if (u >= m+1 && u <= m+n) mark[u-m] = true;
            for(int edge_id : flow.g[u]) {
                Edge e = flow.e[edge_id];
                if (fabs(e.cap - e.flow) > 1e-9 && !visited[e.b]) {
                    qu.push(e.b);
                    visited[e.b] = true;
                }
            }
        }
    }
    return m - mf > 1e-6;
}

int main() {
    freopen("hard.in", "r", stdin);
    freopen("hard.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m) {
        FOR(i,1,m) cin >> eu[i] >> ev[i];
        double l = 0, r = 1e3, res = 0;
        REP(turn,50) {
            double mid = (l + r) / 2.0;
            if (check(mid)) {
                res = mid;
                l = mid;
            }
            else r = mid;
        }
        memset(mark, false, sizeof mark);
        // DEBUG(res);

        check(res, true);
        int cnt = 0;
        FOR(i,1,n) if (mark[i]) ++cnt;

        double sum = 0;
        FOR(i,1,m) if (mark[eu[i]] && mark[ev[i]]) {
            sum += 1;
        }
        if (sum / (double) cnt < m / (double) n) {
            cnt = n;
            FOR(i,1,n) mark[i] = true;
        }
        // DEBUG(sum / (double) cnt);

        if (cnt == 0) {
            cnt = 1;
            mark[1] = true;
        }
        cout << cnt << endl;
        FOR(i,1,n) if (mark[i]) cout << i << endl;
    }
    return 0;
}
