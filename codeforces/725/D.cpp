
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

const int MN = 300111;
const int INF = 1000111000111000111LL;
int n;

struct Team {
  int t, w;

  void read() {
    GI(t);
    GI(w);
  }

  int toKill() { return w - t + 1; }
} a1, a[MN];

bool operator<(const Team& a, const Team& b) { return a.t > b.t; }
int c[MN];

#define _(X) ((X) & (-(X)))

int sum[MN], sl[MN];

int getSum(int u) {
  int res = 0;
  for (; u > 0; u -= _(u)) {
    res += sum[u];
    if (res > INF) res = INF;
  }
  return res;
}
int getSl(int u) {
  int res = 0;
  for (; u > 0; u -= _(u)) res += sl[u];
  return res;
}

void updateSum(int u, int val) {
  for (; u <= n; u += _(u)) {
    sum[u] += val;
    if (sum[u] > INF) sum[u] = INF;
  }
}

void updateSl(int u, int val) {
  for (; u <= n; u += _(u)) sl[u] += val;
}

int id[MN];
pair<int, int> t[MN];
void init() {
  FOR(i, 1, n) t[i] = make_pair(a[i].toKill(), i);
  sort(t + 1, t + n + 1);

  FOR(i, 1, n) id[t[i].second] = i;
}

void update(int u) {
  updateSum(id[u], t[id[u]].first);
  updateSl(id[u], 1);
}

#undef int
int main() {
#define int long long
  while (GI(n) == 1) {
    memset(sum, 0, sizeof sum);
    memset(sl, 0, sizeof sl);
    --n;
    a1.read();
    FOR(i, 1, n) a[i].read();
    sort(a + 1, a + n + 1);

    init();

    FOR(i, 1, n) c[i] = a[i].t;
    int nc = unique(c + 1, c + n + 1) - c - 1;
    c[++nc] = 0;

    int X = 0;
    int better = 0;
    int res = n + 1;

    FOR(i, 1, nc) if (a1.t >= c[i]) {
      // reduce a1.t to c[i]
      X = a1.t - c[i];

      // how many better team?
      while (better < n && a[better + 1].t > c[i]) {
        ++better;
        update(better);
      }

      // can we kill any team?
      int l = 1, r = n, killed = 0;
      while (l <= r) {
        int mid = (l + r) >> 1;
        if (getSum(mid) <= X) {
          killed = mid;
          l = mid + 1;
        } else
          r = mid - 1;
      }

      res = min(res, better - getSl(killed) + 1);
    }
    cout << res << endl;
  }
}
