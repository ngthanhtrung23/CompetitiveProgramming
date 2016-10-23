
#include <bits/stdc++.h>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) \
  { cerr << #X << " = " << (X) << endl; }
#define PR(A, n)                      \
  {                                   \
    cerr << #A << " = ";              \
    FOR(_, 1, n) cerr << A[_] << ' '; \
    cerr << endl;                     \
  }
#define PR0(A, n)                  \
  {                                \
    cerr << #A << " = ";           \
    REP(_, n) cerr << A[_] << ' '; \
    cerr << endl;                  \
  }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

template <class Flow = int, class Cost = int>
struct MinCostFlow {
  const Flow INF_FLOW = 1000111000;
  const Cost INF_COST = 1000111000111000LL;

  int n, t, S, T;
  Flow totalFlow;
  Cost totalCost;
  vector<int> last, visited;
  vector<Cost> dis;
  struct Edge {
    int to;
    Flow cap;
    Cost cost;
    int next;
    Edge(int to, Flow cap, Cost cost, int next)
        : to(to), cap(cap), cost(cost), next(next) {}
  };
  vector<Edge> edges;

  MinCostFlow(int n)
      : n(n),
        t(0),
        totalFlow(0),
        totalCost(0),
        last(n, -1),
        visited(n, 0),
        dis(n, 0) {
    edges.clear();
  }

  int addEdge(int from, int to, Flow cap, Cost cost) {
    edges.push_back(Edge(to, cap, cost, last[from]));
    last[from] = t++;
    edges.push_back(Edge(from, 0, -cost, last[to]));
    last[to] = t++;
    return t - 2;
  }

  pair<Flow, Cost> minCostFlow(int _S, int _T) {
    S = _S;
    T = _T;
    SPFA();
    while (1) {
      while (1) {
        REP(i, n) visited[i] = 0;
        if (!findFlow(S, INF_FLOW)) break;
      }
      if (!modifyLabel()) break;
    }
    return make_pair(totalFlow, totalCost);
  }

 private:
  void SPFA() {
    REP(i, n) dis[i] = INF_COST;
    priority_queue<pair<Cost, int> > Q;
    Q.push(make_pair(dis[S] = 0, S));
    while (!Q.empty()) {
      int x = Q.top().second;
      Cost d = -Q.top().first;
      Q.pop();
      // For double: dis[x] > d + EPS
      if (dis[x] != d) continue;
      for (int it = last[x]; it >= 0; it = edges[it].next)
        if (edges[it].cap > 0 && dis[edges[it].to] > d + edges[it].cost)
          Q.push(make_pair(-(dis[edges[it].to] = d + edges[it].cost),
                           edges[it].to));
    }
    Cost disT = dis[T];
    REP(i, n) dis[i] = disT - dis[i];
  }

  Flow findFlow(int x, Flow flow) {
    if (x == T) {
      totalCost += dis[S] * flow;
      totalFlow += flow;
      return flow;
    }
    visited[x] = 1;
    Flow now = flow;
    for (int it = last[x]; it >= 0; it = edges[it].next)
      // For double: fabs(dis[edges[it].to] + edges[it].cost - dis[x]) < EPS
      if (edges[it].cap && !visited[edges[it].to] &&
          dis[edges[it].to] + edges[it].cost == dis[x]) {
        Flow tmp = findFlow(edges[it].to, min(now, edges[it].cap));
        edges[it].cap -= tmp;
        edges[it ^ 1].cap += tmp;
        now -= tmp;
        if (!now) break;
      }
    return flow - now;
  }

  bool modifyLabel() {
    Cost d = INF_COST;
    REP(i, n)
    if (visited[i])
      for (int it = last[i]; it >= 0; it = edges[it].next)
        if (edges[it].cap && !visited[edges[it].to])
          d = min(d, dis[edges[it].to] + edges[it].cost - dis[i]);

    // For double: if (d > INF_COST / 10)     INF_COST = 1e20
    if (d == INF_COST) return false;
    REP(i, n) if (visited[i]) dis[i] += d;
    return true;
  }
};

int a[3011], b[3011];
int x[3011], y[3011];

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int n, na, nb;
  while (cin >> n >> na >> nb) {
    FOR(i, 1, n) cin >> a[i];
    FOR(i, 1, n) cin >> b[i];

    MinCostFlow<int, int> flow(n + 5);
    int source = 0;
    int sink = n + 1;
    int X = n + 2;
    int Y = n + 3;

    flow.addEdge(source, X, na, 0);
    flow.addEdge(source, Y, nb, 0);
    FOR(i, 1, n) {
      x[i] = flow.addEdge(X, i, 1, -a[i]);
      y[i] = flow.addEdge(Y, i, 1, -b[i]);
      flow.addEdge(i, sink, 1, 0);
    }
    auto t = flow.minCostFlow(source, sink);
    cout << -t.second << endl;
    vector<int> res1, res2;
    FOR(i, 1, n) if (flow.edges[x[i]].cap == 0) { res1.push_back(i); }
    FOR(i, 1, n) if (flow.edges[y[i]].cap == 0) { res2.push_back(i); }

    for (int x : res1) cout << x << ' ';
    cout << endl;
    for (int x : res2) cout << x << ' ';
    cout << endl;
    cout << endl;
  }
}
