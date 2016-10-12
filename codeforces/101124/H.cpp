
#include <bits/stdc++.h>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) \
  { cout << #X << " = " << (X) << endl; }
#define PR(A, n)                      \
  {                                   \
    cout << #A << " = ";              \
    FOR(_, 1, n) cout << A[_] << ' '; \
    cout << endl;                     \
  }
#define PR0(A, n)                  \
  {                                \
    cout << #A << " = ";           \
    REP(_, n) cout << A[_] << ' '; \
    cout << endl;                  \
  }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

const int MN = 100111;
int up[MN], down[MN], tableWith[MN];
int a[MN], cycleId[MN], cyclePos[MN];
vector<int> cycles[MN];

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int n, k;
  while (GI(n) == 1 && GI(k) == 1) {
    FOR(i, 1, n) cycles[i].clear();
    memset(cycleId, -1, sizeof cycleId);

    FOR(i, 1, n) {
      GI(up[i]);
      GI(down[i]);
      tableWith[up[i]] = i;
    }
    FOR(i, 1, n) a[i] = tableWith[down[i]];
    //    PR(a, n);

    int nCycle = 0;
    FOR(i, 1, n) if (cycleId[i] < 0) {
      int u = i;
      ++nCycle;
      do {
        cycleId[u] = nCycle;
        cyclePos[u] = SZ(cycles[nCycle]);
        cycles[nCycle].push_back(u);
        u = a[u];
      } while (cycleId[u] < 0);
    }
    //    PR(cycleId, n);
    //    PR(cyclePos, n);

    FOR(i, 1, k) {
      int u, time;
      GI(u);
      GI(time);
      int pos = (cyclePos[u] + time) % SZ(cycles[cycleId[u]]);
      printf("%lld\n", cycles[cycleId[u]][pos]);
    }
  }
}
