
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

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int n;
  string s;
  while (cin >> n >> s) {
    int res = 0;
    int i = 0;
    while (i < n && s[i] == '<') ++i, ++res;

    i = n - 1;
    while (i >= 0 && s[i] == '>') --i, ++res;

    cout << res << endl;
  }
}
