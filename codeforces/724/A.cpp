
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

int get(string s) {
  if (s == "monday") return 0;
  if (s == "tuesday") return 1;
  if (s == "wednesday") return 2;
  if (s == "thursday") return 3;
  if (s == "friday") return 4;
  if (s == "saturday") return 5;
  return 6;
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  string a, b;
  while (cin >> a >> b) {
    int u, v; u = get(a); v = get(b);
    if (u == v || (u + 2) % 7 == v || (u + 3) % 7 == v) {
      cout << "YES";
    }
    else cout << "NO";
    cout << endl;
  }
}
