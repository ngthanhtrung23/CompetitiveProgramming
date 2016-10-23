
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

int k, a[55], b[55];

#undef int
int main() {
#define int long long
  int ntest;
  cin >> ntest;
  while (ntest--) {
    int n;
    cin >> n;
    k = 0;
    for (int i = 1; i <= n; i += 2) {
      if (i == n) {
        ++k;
        a[k] = b[k] = i;
      } else {
        cout << "? " << i << ' ' << i + 1 << endl;
        char c;
        cin >> c;
        ++k;
        if (c == '=')
          a[k] = b[k] = i;
        else if (c == '>') {
          b[k] = i;
          a[k] = i + 1;
        } else if (c == '<') {
          b[k] = i + 1;
          a[k] = i;
        }
      }
    }
    int nn = a[1];
    FOR(i, 2, k) {
      cout << "? " << nn << ' ' << a[i] << endl;
      char c;
      cin >> c;
      if (c == '>') nn = a[i];
    }
    int ln = b[1];
    FOR(i, 2, k) {
      cout << "? " << ln << ' ' << b[i] << endl;
      char c;
      cin >> c;
      if (c == '<') ln = b[i];
    }
    cout << "! " << nn << ' ' << ln << endl;
  }
}
