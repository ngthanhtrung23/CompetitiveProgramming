#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

struct Plant {
    int l, r, a, b, c;
    map<int,int> id;

    int get(int x) {
        return a * x * x + b * x + c;
    }
} a[55];

struct Cond {
    int u, v, d;
} cond[111];

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};
#define LL long long
struct PushRelabel {
  int N;
  vector<vector<Edge> > G;
  vector<LL> excess;
  vector<int> dist, active, count;
  queue<int> Q;

  PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(int from, int to, int cap) {
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }
  void Enqueue(int v) { 
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); } 
  }
  void Push(Edge &e) {
    int amt = (int)(min(excess[e.from], (LL)(e.cap - e.flow)));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;    
    excess[e.from] -= amt;
    Enqueue(e.to);
  }
  void Gap(int k) {
    for (int v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }
  void Relabel(int v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (int i = 0; i < G[v].size(); i++) 
      if (G[v][i].cap - G[v][i].flow > 0)
    dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }
  void Discharge(int v) {
    for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1) 
    Gap(dist[v]); 
      else
    Relabel(v);
    }
  }
  LL GetMaxFlow(int s, int t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (int i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }
    LL totflow = 0;
    for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
};

const int MAX = 1000111;

int main() {
    ios :: sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        FOR(i,1,n) cin >> a[i].a >> a[i].b >> a[i].c;
        FOR(i,1,n) cin >> a[i].l >> a[i].r;

        FOR(i,1,m) cin >> cond[i].u >> cond[i].v >> cond[i].d;

        int source = 0;
        int nNode = 1;
        FOR(i,1,n) {
            FOR(x,a[i].l-1,a[i].r) {
                a[i].id[x] = nNode++;
            }
        }
        int sink = nNode++;

        PushRelabel flow(nNode);
        FOR(i,1,n) {
            flow.AddEdge(source, a[i].id[a[i].l-1], 2000111000);
            FOR(x,a[i].l,a[i].r) {
                flow.AddEdge(a[i].id[x-1], a[i].id[x], MAX - a[i].get(x));
            }
            flow.AddEdge(a[i].id[a[i].r], sink, 2000111000);
        }

        FOR(i,1,m) {
            int u = cond[i].u, v = cond[i].v, d = cond[i].d;
            FOR(x,a[u].l-1,a[u].r) {
                int y = x - d;
                if (y >= a[v].l-1 && y <= a[v].r) {
                    flow.AddEdge(a[u].id[x], a[v].id[y], 2000111000);
                }
            }
        }

        long long res = flow.GetMaxFlow(source, sink);
        cout << MAX * n - res << endl;
    }
    return 0;
}
