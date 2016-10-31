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

struct Edge {
  int u, v;
  int w, c;
  int id;
} e[MN];

bool operator<(const Edge& a, const Edge& b) { return a.w < b.w; }

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

int inMst[MN];
int n, m;
vector<pair<int, int> > ke[MN];
int h[MN];

int father[20][MN];
pair<int, int> ln[20][MN];

void addEdge(int u, int v, int id) {
  ke[u].emplace_back(v, id);
  ke[v].emplace_back(u, id);
}

void dfs(int u, int fu) {
  for (auto p : ke[u]) {
    int v = p.first;
    if (v == fu) continue;

    h[v] = h[u] + 1;
    father[0][v] = u;

    int i = p.second;
    ln[0][v] = make_pair(e[i].w, i);

    dfs(v, u);
  }
}

void initLCA() {
  FOR(t, 1, 19) {
    FOR(u, 1, n) {
      int v = father[t - 1][u];
      father[t][u] = father[t - 1][v];
      ln[t][u] = max(ln[t - 1][u], ln[t - 1][v]);
    }
  }
}

pair<int, int> getMax(int u, int v) {
  pair<int, int> res = make_pair(-1, 0);
  if (h[u] < h[v]) swap(u, v);

  if (h[u] > h[v]) {
    FORD(t, 19, 0) {
      int x = father[t][u];
      if (h[x] >= h[v]) {
        res = max(res, ln[t][u]);
        u = father[t][u];
      }
    }
  }
  if (u == v) return res;

  FORD(t, 19, 0) {
    if (father[t][u] != father[t][v]) {
      res = max(res, ln[t][u]);
      res = max(res, ln[t][v]);
      u = father[t][u];
      v = father[t][v];
    }
  }

  res = max(res, ln[0][u]);
  res = max(res, ln[0][v]);

  return res;
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  while (GI(n) == 1 && GI(m) == 1) {
    FOR(i, 1, n) ke[i].clear();
    FOR(i, 1, m) GI(e[i].w);
    FOR(i, 1, m) GI(e[i].c);
    FOR(i, 1, m) {
      GI(e[i].u);
      GI(e[i].v);
      e[i].id = i;
    }
    int S;
    GI(S);

    // find MST
    sort(e + 1, e + m + 1);
    DSU dsu;
    dsu.init(n + 1);
    int sumw = 0;
    int minc = 1000111000;
    memset(inMst, 0, sizeof inMst);
    FOR(i, 1, m) {
      int u = dsu.getRoot(e[i].u);
      int v = dsu.getRoot(e[i].v);
      if (u != v) {
        dsu.merge(u, v);
        minc = min(minc, e[i].c);
        sumw += e[i].w;
        inMst[i] = 1;

        addEdge(e[i].u, e[i].v, i);
      }
    }
    int res = sumw - (S / minc);
    int removeEdge = -1;
    int addedEdge = -1;
    int minEdge = -1;

    // init LCA
    h[1] = 1;
    memset(father, 0, sizeof father);
    dfs(1, -1);
    initLCA();

    // we try to add 1 edge & remove 1 edge
    FOR(i, 1, m) if (!inMst[i] && e[i].c < minc) {
      int u = e[i].u, v = e[i].v;
      auto rem = getMax(u, v);

      int cur = sumw - rem.first + e[i].w;
      cur -= S / e[i].c;

      if (cur < res) {
        res = cur;
        addedEdge = i;
        removeEdge = rem.second;
      }
    }

    // find which edge is minEdge
    FOR(i, 1, m) {
      if (i == addedEdge || (inMst[i] && !(removeEdge == i))) {
        if (minEdge < 0 || e[i].c < e[minEdge].c) {
          minEdge = i;
        }
      }
    }
    printf("%lld\n", res);
    FOR(i, 1, m) {
      if (i == addedEdge || (inMst[i] && !(removeEdge == i))) {
        printf("%lld ", e[i].id);
        if (i == minEdge) {
          e[i].w -= S / e[i].c;
        }
        printf("%lld\n", e[i].w);
      }
    }
  }
}
