#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

#define _MAX_COST 1000111
#define _MAX_FLOW 1000111

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
   pair<Flow, Cost> minCostFlow(int vs, int vt) { //flow,cost
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

         if (dist[vt] == MAX_COST)
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

MinCostFlow<int,int> mcmf;

string t, s[333];
int cnt[333];
int l[333], r[333], a[333];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> t) {
        int lt = t.length();
        memset(cnt, 0, sizeof cnt);
        REP(i,lt) {
            cnt[t[i]]++;
        }
        mcmf.E.clear();
        int start = mcmf.addV();
        int target = mcmf.addV();

        int n; cin >> n;
        FOR(i,1,n) l[i] = mcmf.addV();
        FOR(i,'a','z') {
            r[i] = mcmf.addV();
        }

        FOR(i,1,n) cin >> s[i] >> a[i];

        FOR(i,'a','z') {
            mcmf.addEdge(r[i], target, cnt[i], 0);
        }
        FOR(i,1,n) {
            mcmf.addEdge(start, l[i], a[i], i);

            memset(cnt, 0, sizeof cnt);
            REP(x,s[i].length()) {
                cnt[s[i][x]]++;
            }

            FOR(j,'a','z') {
                mcmf.addEdge(l[i], r[j], cnt[j], 0);
            }
        }
        pair<int,int> res = mcmf.minCostFlow(start, target);

        if (res.F < lt) cout << -1 << endl;
        else cout << res.S << endl;
    }
    return 0;
}
