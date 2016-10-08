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

const int MN = 22;

int a[22][22], m, n;

void swapCol(int u, int v) {
  FOR(i,1,m) swap(a[i][u], a[i][v]);
}

bool check2() {
  FOR(i,1,m) {
    int wrong = 0;
    FOR(j,1,n) if (a[i][j] != j) ++wrong;
    if (wrong != 0 && wrong != 2) return false;
  }
  return true;
}

bool check() {
  if (check2()) return true;
  FOR(i,1,n) FOR(j,i+1,n) {
    swapCol(i, j);
    if (check2()) return true;
    swapCol(i, j);
  }
  return false;
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  while (cin >> m >> n) {
    FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

    cout << (check() ? "YES" : "NO") << endl;
  }
}
