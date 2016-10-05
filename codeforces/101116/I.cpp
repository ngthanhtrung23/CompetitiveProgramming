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

int cnt[55];

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int ntest;
  cin >> ntest;
  while (ntest--) {
    int n;
    cin >> n;
    memset(cnt, 0, sizeof cnt);
    FOR(i, 1, n) {
      FOR(j, 1, 6) {
        int a;
        cin >> a;
        ++cnt[a];
      }
    }

    vector<pair<int, int> > x;
    FOR(i, 1, 49) {
      if (i == 7)
        x.emplace_back(-cnt[i], -i);
      else
        x.emplace_back(-cnt[i], i);
    }
    sort(x.begin(), x.end());

    vector<int> res;
    REP(i, 6) res.push_back(llabs(x[i].second));
    sort(res.begin(), res.end());
    for (int x : res) cout << x << ' ';

    cout << '\n';
  }
}
