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
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
// Fastest flow
// Index from 0, directed
// To use:
// MaxFlow flow(n)
// For each edge: flow.addEdge(u, v, c)
// result = flow.getFlow(s, t)

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

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    GN(n); GN(m);
    MaxFlow flow(n);
    while (m--) {
        int u, v, c; GN(u); GN(v); GN(c);
        --u; --v;
        flow.addEdge(u, v, c, true);
    }
    int res = flow.getFlow(0, n-1);

    for(int i = 0; i < flow.edges.size(); i += 2) {
        if (flow.edges[i].f >= 0) {
            puts("0");
        }
        else {
            puts("1");
        }
    }
}

