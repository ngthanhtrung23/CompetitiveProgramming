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

const int MN = 111;
const int MM = 10111;
const int oo = 1000111000;
int n, m, c[MN][MN];
int eu[MM], ev[MM], ec[MM];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m) {
        FOR(i,1,n) FOR(j,1,n) c[i][j] = oo;
        FOR(i,1,n) c[i][i] = 0;
        FOR(i,1,m) {
            int u, v, l; cin >> u >> v >> l;
            ++u; ++v;
            eu[i] = u; ev[i] = v; ec[i] = l;
            c[u][v] = min(c[u][v], l);
            c[v][u] = c[u][v];
        }
        FOR(k,1,n) FOR(i,1,n) FOR(j,1,n) c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

        if (c[1][n] == oo) {
            cout << 0 << endl;
            continue;
        }

        MaxFlow flow(2*n);
        FOR(i,1,n) {
            int c = (i == 1 || i == n) ? oo : 1;
            flow.addEdge(2*i-2, 2*i-1, c);
        }
        FOR(i,1,m) {
            if (c[1][eu[i]] + ec[i] + c[ev[i]][n] == c[1][n])
                flow.addEdge(2*eu[i]-1, 2*ev[i]-2, oo);
            if (c[1][ev[i]] + ec[i] + c[eu[i]][n] == c[1][n])
                flow.addEdge(2*ev[i]-1, 2*eu[i]-2, oo);
        }
        int res = flow.getMaxFlow(0, 2*n-1);
        if (res >= oo) cout << "IMPOSSIBLE" << endl;
        else cout << res << endl;
    }
    return 0;
}
