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

struct Edge {
    int u, v, c, f;
    int next;
};

struct MaxFlow {
    int n, s, t;
    vector< Edge > edges;
    vector<int> head, current, h, avail;
    vector<long long> excess;

    MaxFlow(int n) : n(n), head(n, -1), current(n, -1), h(n), avail(n), excess(n) {
        edges.clear();
    }

    void addEdge(int u, int v, int c, bool bi = false) {
        Edge xuoi = {u, v, c, 0, head[u]};
        head[u] = edges.size(); edges.push_back(xuoi);
        Edge nguoc = {v, u, bi ? c : 0, 0, head[v]};
        head[v] = edges.size(); edges.push_back(nguoc);
    }

    long long getFlow(int _s, int _t) {
        s = _s; t = _t;
        init();

        int now = 0;
        queue<int> qu[2];
        REP(x,n)
            if (x != s && x != t && excess[x] > 0)
                qu[now].push(x);
        
        globalLabeling();

        int cnt = 0;
        while (!qu[now].empty()) {
            while (!qu[1-now].empty()) qu[1-now].pop();

            while (!qu[now].empty()) {
                int x = qu[now].front(); qu[now].pop();
                while (current[x] >= 0) {
                    int p = current[x];
                    if (edges[p].c > edges[p].f && h[edges[p].u] > h[edges[p].v]) {
                        bool need = (edges[p].v != s && edges[p].v != t && !excess[edges[p].v]);
                        push(current[x]);
                        if (need) qu[1-now].push(edges[p].v);
                        if (!excess[x]) break;
                    }
                    current[x] = edges[current[x]].next;
                }
                
                if (excess[x] > 0) {
                    lift(x);
                    current[x] = head[x];
                    qu[1-now].push(x);
                    cnt++;
                    if (cnt == n) {
                        globalLabeling();
                        cnt=0;
                    }
                }
            }
            now = 1 - now;
        }
        return excess[t];
    }

private:
    void init() {
        REP(i,n) current[i] = head[i];

        int p = head[s];
        while (p >= 0) {
            edges[p].f = edges[p].c;
            edges[p^1].f -= edges[p].c;
            excess[edges[p].v] += edges[p].c;
            excess[s] -= edges[p].c;
            p = edges[p].next;
        }
        FOR(v,0,n-1) h[v] = 1;
        h[s] = n; h[t] = 0;
    }

    void push(int i) {
        long long delta = min(excess[edges[i].u], (long long) edges[i].c - edges[i].f);
        edges[i].f += delta; edges[i^1].f -= delta;
        excess[edges[i].u] -= delta;
        excess[edges[i].v] += delta;
    }

    void lift(int u) {
        int minH = 2 * n;
        int p = head[u];
        while (p>=0) {
            if (edges[p].c > edges[p].f)
                minH = min(minH, h[edges[p].v]);
            p = edges[p].next;
        }
        h[u] = minH + 1;
    }

    void globalLabeling() {
        REP(i,n) avail[i] = 1, h[i] = 0;
        h[s] = n; h[t] = 0;
        queue<int> q; q.push(t); avail[t] = false;

        while (!q.empty()) {
            int x = q.front(); q.pop();
            int p = head[x];
            while (p >= 0) {
                int pp = p^1;
                if (avail[edges[pp].u] && edges[pp].f < edges[pp].c) {
                    h[edges[pp].u] = h[x] + 1;
                    avail[edges[pp].u] = 0;
                    q.push(edges[pp].u);
                }
                p = edges[p].next;
            }
            if (q.empty() && avail[s]) {
                avail[s] = false;
                q.push(s);
            }
        }
        REP(x,n) current[x] = head[x];
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
        cout << flow.getFlow(0, 2*n*n+1) << endl;
    }
    return 0;
}
