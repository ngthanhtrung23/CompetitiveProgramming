
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

struct Seg {
  int l, r;
  Seg(int l, int r) : l(l), r(r) {}
  Seg() {}
} a[211];

bool intersect(const Seg& a, const Seg& b) {
  if (a.r < b.l) return false;
  if (a.l > b.r) return false;
  return true;
}
bool can(int l, int r, int n) {
  Seg cur(l, r);
  FOR(i, 1, n) if (intersect(a[i], cur)) return false;
  return true;
}
int n;

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  while (cin >> n) {
    FOR(i, 1, n) {
      int s, d;
      cin >> s >> d;
      if (can(s, s + d - 1, i - 1)) {
        a[i] = Seg(s, s + d - 1);
        continue;
      }
      if (can(1, d, i - 1)) {
        a[i] = Seg(1, d);
        continue;
      }

      int nn = 2000111000111LL;
      FOR(j, 1, i - 1) {
        int l = a[j].r + 1;
        if (can(l, l + d - 1, i - 1)) {
          nn = min(nn, l);
        }
      }
      a[i] = Seg(nn, nn + d - 1);
    }

    FOR(i, 1, n) cout << a[i].l << ' ' << a[i].r << '\n';
  }
}
