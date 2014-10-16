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
/*
 * mincostflow implementation. Vertex indices from 0
 * Usage:
 *   for i = 1..N: int v = mcf.addV();
 *   for i = 1..E: MinCostFlow<int,int>::Edge* e = mcf.addEdge(u, v, flow, cost);
 *   mcf.minCostFlow --> return pair<flow, cost>
 * DANGEROUS!!!!!!! If need to find flow through each edge, remember that there can
 * be flow through both (u, v) and (v, u)
 */

// Slow version (Ford Bellman)

#define _MAX_COST 1000111000111000LL
#define _MAX_FLOW 1000111000

// Must be careful when used with double.
template<class Flow = int, class Cost = int>
struct MinCostFlow {
    struct Edge {
        int t;
        Flow f;
        Cost c;
        Edge*next, *rev;
        Edge(int _t, Flow _f, Cost _c, Edge*_next) :
                t(_t), f(_f), c(_c), next(_next) {
        }
    };
    vector<Edge*> E;

    int addV() {
        E.push_back((Edge*) 0);
        return E.size() - 1;
    }
    Edge* makeEdge(int s, int t, Flow f, Cost c) {
        return E[s] = new Edge(t, f, c, E[s]);
    }
    Edge* addEdge(int s, int t, Flow f, Cost c) {
        Edge*e1 = makeEdge(s, t, f, c), *e2 = makeEdge(t, s, 0, -c);
        e1->rev = e2, e2->rev = e1;
        return e1;
    }
    pair<Flow, Cost> minCostFlow(int vs, int vt) {
        int n = E.size();
        Flow flow = 0;
        Cost cost = 0;
        const Cost MAX_COST = _MAX_COST;
        const Flow MAX_FLOW = _MAX_FLOW;
        for (;;) {
            vector<Cost> dist(n, MAX_COST);
            vector<Flow> am(n, 0);
            vector<Edge*> prev(n);
            vector<bool> inQ(n, false);
            queue<int> que;

            dist[vs] = 0;
            am[vs] = MAX_FLOW;
            que.push(vs);
            inQ[vs] = true;

            while (!que.empty()) {
                int u = que.front();
                Cost c = dist[u];
                que.pop();
                inQ[u] = false;
                for (Edge*e = E[u]; e; e = e->next)
                    if (e->f > 0) {
                        Cost nc = c + e->c;
                        if (nc < dist[e->t]) {
                            dist[e->t] = nc;
                            prev[e->t] = e;
                            am[e->t] = min(am[u], e->f);
                            if (!inQ[e->t]) {
                                que.push(e->t);
                                inQ[e->t] = true;
                            }
                        }
                    }
            }

            if (dist[vt] == MAX_COST) // careful with double
                break;
            Flow by = am[vt];
            int u = vt;
            flow += by;
            cost += by * dist[vt];
            while (u != vs) {
                Edge*e = prev[u];
                e->f -= by;
                e->rev->f += by;
                u = e->rev->t;
            }
        }
        return make_pair(flow, cost);
    }
};


const int MN = 2011;
struct Work {
    int s, t, c;
    MinCostFlow<int, long long>::Edge* edge;
} a[MN];
int n, k, c[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i].s >> a[i].t >> a[i].c;
        int s = 0;
        FOR(i,1,n) c[++s] = a[i].s, c[++s] = a[i].s + a[i].t - 1;
        sort(c+1, c+s+1);
        s = unique(c+1, c+s+1) - c - 1;

        MinCostFlow<int,long long> flow;
        REP(i,s+2) flow.addV();
        REP(i,s+1) flow.addEdge(i, i+1, k, 0);

        FOR(i,1,n) {
            int from = lower_bound(c+1, c+s+1, a[i].s) - c;
            int to = lower_bound(c+1, c+s+1, a[i].s + a[i].t - 1) - c;

            a[i].edge = flow.addEdge(from, to + 1, 1, -a[i].c);
        }
        auto res = flow.minCostFlow(0, s+1);

        FOR(i,1,n)
            if (a[i].edge->f == 0) cout << "1 ";
            else cout << "0 ";
        cout << endl;
    }
    return 0;
}
