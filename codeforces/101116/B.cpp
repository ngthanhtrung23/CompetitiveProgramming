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

string a[411];
int row[411], col[411];

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int ntest;
  cin >> ntest;
  while (ntest--) {
    int m, n;
    cin >> m >> n;
    FOR(i, 1, m) {
      cin >> a[i];
      reverse(a[i].begin(), a[i].end());
      a[i] = " " + a[i];
    }

    int res = 0;
    memset(row, 0, sizeof row);
    memset(col, 0, sizeof col);
    FOR(i, 1, m) FOR(j, 1, n) {
      int cur = a[i][j] - '0';
      if (row[i]) cur = 1 - cur;
      if (col[j]) cur = 1 - cur;

      if (cur == 0) {
        row[i] ^= 1;
        col[j] ^= 1;
        ++res;
      }
    }
    cout << res << '\n';
  }
}
