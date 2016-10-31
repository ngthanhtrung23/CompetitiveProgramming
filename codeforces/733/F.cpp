
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

const int MN = 200111;

int lab[MN];
struct DSU {
  void init(int n) { REP(i, n + 1) lab[i] = -1; }

  int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
  }

  bool merge(int u, int v) {
    u = getRoot(u);
    v = getRoot(v);
    if (u == v) return false;
    if (lab[u] > lab[v]) swap(u, v);
    lab[u] += lab[v];
    lab[v] = u;
    return true;
  }
};
DSU dsu;

int n, m;
struct Edge {
  int u, v;
  int c, w;
  int id;
} edges[MN];
bool operator<(const Edge& a, const Edge& b) { return a.w < b.w; }

vector<pair<int, int> > ke[MN];
void addEdge(int u, int v, int id) {
  ke[u].emplace_back(v, id);
  ke[v].emplace_back(u, id);
}

int h[MN];
int father[18][MN];
pair<int, int> ln[18][MN];

void dfs(int u, int fu) {
  for (auto p : ke[u]) {
    int v = p.first;
    if (v == fu) continue;
    int id = p.second;

    h[v] = h[u] + 1;
    father[0][v] = u;
    ln[0][v] = make_pair(edges[id].w, id);

    dfs(v, u);
  }
}

void initLCA() {
  FOR(t, 1, 17) {
    FOR(u, 1, n) {
      int v = father[t - 1][u];
      father[t][u] = father[t - 1][v];
      ln[t][u] = max(ln[t - 1][u], ln[t - 1][v]);
    }
  }
}

pair<int, int> lca(int u, int v) {
  assert(u != v);
  if (h[u] < h[v]) swap(u, v);
  pair<int, int> res = make_pair(-1, 0);
  if (h[u] > h[v]) {
    FORD(t, 17, 0) {
      int x = father[t][u];
      if (h[x] >= h[v]) {
        res = max(res, ln[t][u]);
        u = x;
      }
    }
  }
  assert(h[u] == h[v]);
  if (u == v) return res;

  FORD(t, 17, 0) {
    if (father[t][u] != father[t][v]) {
      res = max(res, ln[t][u]);
      res = max(res, ln[t][v]);

      u = father[t][u];
      v = father[t][v];
    }
  }
  assert(father[0][u] == father[0][v]);
  res = max(res, ln[0][u]);
  res = max(res, ln[0][v]);
  return res;
}

int inMst[MN];

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  while (GI(n) == 1 && GI(m) == 1) {
    FOR(i, 1, n) ke[i].clear();
    FOR(i, 1, m) GI(edges[i].w);
    FOR(i, 1, m) GI(edges[i].c);
    FOR(i, 1, m) {
      GI(edges[i].u);
      GI(edges[i].v);
      edges[i].id = i;
    }
    int S;
    GI(S);
    sort(edges + 1, edges + m + 1);

    // find MST
    dsu.init(n);
    int sumw = 0;
    int minc = 1000111000;
    memset(inMst, 0, sizeof inMst);
    FOR(i, 1, m) {
      int u = dsu.getRoot(edges[i].u);
      int v = dsu.getRoot(edges[i].v);

      if (u != v) {
        inMst[i] = 1;
        dsu.merge(u, v);
        sumw += edges[i].w;
        minc = min(minc, edges[i].c);
        addEdge(edges[i].u, edges[i].v, i);
      }
    }
    int res = sumw - S / minc;

    // init LCA
    h[1] = 1;
    dfs(1, -1);
    initLCA();

    // swap 1 edge
    int add = -1, rem = -1;
    FOR(i, 1, m) if (!inMst[i] && edges[i].c < minc) {
      int u = edges[i].u, v = edges[i].v;
      auto t = lca(u, v);

      int cur = sumw - t.first + edges[i].w - S / edges[i].c;
      if (cur < res) {
        res = cur;
        add = i;
        rem = t.second;
      }
    }
    if (add >= 0) {
      inMst[add] = 1;
      inMst[rem] = 0;
      minc = edges[add].c;
    }

    printf("%lld\n", res);
    int saveMin = -1;
    FOR(i, 1, m) if (inMst[i]) {
      if (saveMin < 0 || edges[i].c < edges[saveMin].c) saveMin = i;
    }

    FOR(i, 1, m) if (inMst[i]) {
      printf("%lld ", edges[i].id);
      int w = edges[i].w;
      if (i == saveMin) w -= S / minc;
      printf("%lld\n", w);
    }
  }
}
