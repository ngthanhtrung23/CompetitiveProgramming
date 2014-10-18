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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
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

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int n, t, startx, starty;
char scientistMap[22][22], locationMap[22][22];
int d[22][22][22][22];

void bfs(int turn, int u, int v) {
    int curu = u, curv = v;
    queue<int> qu, qv;
    qu.push(u); qv.push(v);
    d[u][v][u][v] = 0;

    while (!qu.empty()) {
        u = qu.front(); qu.pop();
        v = qv.front(); qv.pop();

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 1 || uu > n || vv < 1 || vv > n || locationMap[uu][vv] == 'Y') continue;
            if (d[curu][curv][uu][vv] >= 0) continue;

            if (turn && d[startx][starty][uu][vv] >= 0 && d[curu][curv][u][v] + 1 > d[startx][starty][uu][vv]) continue;

            if (turn && d[startx][starty][uu][vv] >= 0 && d[curu][curv][u][v] + 1 == d[startx][starty][uu][vv]) {
                if (locationMap[uu][vv] >= '1' && locationMap[uu][vv] <= '9') {
                    d[curu][curv][uu][vv] = d[curu][curv][u][v] + 1;
                    continue;
                }
                continue;
            }

            d[curu][curv][uu][vv] = d[curu][curv][u][v] + 1;
            qu.push(uu);
            qv.push(vv);
        }
    }
}

int id[22][22];

int main() {
    while (cin >> n >> t) {
        FOR(i,1,n) FOR(j,1,n) cin >> scientistMap[i][j];
        FOR(i,1,n) FOR(j,1,n) cin >> locationMap[i][j];
        memset(d, -1, sizeof d);

        FOR(i,1,n) FOR(j,1,n) if (locationMap[i][j] == 'Z') {
            startx = i;
            starty = j;
            bfs(0, i, j);
        }

        int cur = 0;
        FOR(i,1,n) FOR(j,1,n) id[i][j] = ++cur;

        MaxFlow flow(2*n*n+2);
        FOR(i,1,n) FOR(j,1,n) {
            if (scientistMap[i][j] >= '1' && scientistMap[i][j] <= '9')
                flow.addEdge(0, id[i][j], scientistMap[i][j] - '0');
            if (locationMap[i][j] >= '1' && locationMap[i][j] <= '9')
                flow.addEdge(n*n+id[i][j], 2*n*n+1, locationMap[i][j] - '0');
        }

        FOR(i,1,n) FOR(j,1,n) if (scientistMap[i][j] >= '1' && scientistMap[i][j] <= '9') {
            bfs(1, i, j);

            FOR(u,1,n) FOR(v,1,n) if (locationMap[u][v] >= '1' && locationMap[u][v] <= '9')
                if (d[i][j][u][v] >= 0 && d[i][j][u][v] <= t) {
                    flow.addEdge(id[i][j], n*n+id[u][v], min(locationMap[u][v] - '0', scientistMap[i][j] - '0'));
                }
        }
        cout << flow.getMaxFlow(0, 2*n*n+1) << endl;
    }
    return 0;
}
