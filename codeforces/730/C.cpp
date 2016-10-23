#include <bits/stdc++.h>
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
int GI(int& x) { return scanf("%d", &x); }

const int MN = 5011;
int n;
int c[MN][MN];
int f[MN];
vector<int> ke[MN];

struct Store {
  int u;
  int nShovel;
  int price;

  void read() {
    GI(u);
    GI(nShovel);
    GI(price);
  }
} stores[MN];
int nStore;

bool operator<(const Store& a, const Store& b) { return a.price < b.price; }

void init() { FOR(i, 1, n) ke[i].clear(); }

void bfs(int start) {
  memset(f, -1, sizeof f);
  queue<int> qu;
  qu.push(start);
  f[start] = 0;
  while (!qu.empty()) {
    int u = qu.front();
    qu.pop();
    for (int v : ke[u]) {
      if (f[v] < 0) {
        f[v] = f[u] + 1;
        qu.push(v);
      }
    }
  }
  FOR(i, 1, n) {
    if (f[i] < 0)
      c[start][i] = 1000111000;
    else
      c[start][i] = f[i];
  }
}

ll getCost(int city, int maxDist, int need) {
  ll res = 0;
  FOR(i, 1, nStore) {
    if (c[city][stores[i].u] > maxDist) continue;

    ll can = min(need, stores[i].nShovel);
    res += can * stores[i].price;
    need -= can;
    if (need == 0) return res;
  }
  if (need > 0) return 1000111000;
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  int m;
  while (GI(n) == 1) {
    GI(m);
    init();
    while (m--) {
      int u, v;
      GI(u);
      GI(v);
      ke[u].push_back(v);
      ke[v].push_back(u);
    }

    FOR(i, 1, n) { bfs(i); }

    GI(nStore);
    FOR(i, 1, nStore) stores[i].read();
    sort(stores + 1, stores + nStore + 1);

    int totalShovel = 0;
    FOR(i, 1, nStore) totalShovel += stores[i].nShovel;

    int nQuery;
    GI(nQuery);
    FOR(query, 1, nQuery) {
      int city, need, cost;
      GI(city);
      GI(need);
      GI(cost);
      if (need > totalShovel) {
        puts("-1");
        continue;
      }
      int l = 0, r = n, res = -1;
      while (l <= r) {
        int mid = (l + r) >> 1;
        if (getCost(city, mid, need) <= cost) {
          res = mid;
          r = mid - 1;
        } else
          l = mid + 1;
      }
      printf("%d\n", res);
    }
  }
}
