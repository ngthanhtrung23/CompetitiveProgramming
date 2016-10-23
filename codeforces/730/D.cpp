
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
int n, r;
int l[MN], t[MN];

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  const int MAX = 100000;
  while (GI(n) == 1) {
    GI(r);
    bool ok = true;
    FOR(i, 1, n) {
      GI(l[i]);
      l[i] *= 2;
    }
    FOR(i, 1, n) {
      GI(t[i]);
      if (t[i] * 2 < l[i]) ok = false;
    }
    if (!ok) {
      cout << -1 << endl;
      continue;
    }

    int currentTime = 0;
    int effect = 0;
    int res = 0;
    vector<int> trace;
    FOR(i, 1, n) {
      if (effect > 0) {
        // still under effect of magical drink
        if (effect * 2 >= l[i]) {
          effect -= l[i] / 2;
          currentTime += l[i] / 2;
          continue;
        } else {
          l[i] -= effect * 2;
          t[i] -= effect;
          currentTime += effect;
          effect = 0;
        }
      }
      assert(effect == 0);
      if (l[i] <= t[i]) {
        currentTime += l[i];
        continue;
      }
      int leastEnergyTime = l[i] - t[i];
      assert(leastEnergyTime > 0);

      int added = (leastEnergyTime + r - 1) / r;
      res += added;
      effect = added * r - leastEnergyTime;
      assert(effect <= r);

      if (res > MAX) continue;

      currentTime += t[i] - leastEnergyTime;
      REP(turn, added) { trace.push_back(currentTime + turn * r); }

      currentTime += leastEnergyTime;
    }
    printf("%lld\n", res);
    if (res <= MAX) {
      assert(SZ(trace) == res);
      REP(i, SZ(trace) - 1) {
        assert(trace[i] + r <= trace[i + 1]);
        assert(0 <= trace[i]);
      }
      for (int x : trace) printf("%lld ", x);
      puts("");
    }
  }
}
