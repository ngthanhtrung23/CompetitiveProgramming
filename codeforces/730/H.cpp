
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

string a[111];
int nGood, nBad;
string good[111], bad[111];
bool isGood[111];

string mostSpecific() {
  string res = "";
  REP(i, SZ(good[1])) {
    char c = good[1][i];
    FOR(u, 2, nGood)
    if (good[u][i] != c) {
      c = '?';
      break;
    }
    res += c;
  }
  return res;
}

bool match(string pat, string s) {
  if (SZ(s) != SZ(pat)) return false;
  REP(i, SZ(s)) {
    if (pat[i] != '?' && pat[i] != s[i]) return false;
  }
  return true;
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int n, m;
  while (cin >> n >> m) {
    FOR(i, 1, n) cin >> a[i];
    memset(isGood, 0, sizeof isGood);
    nGood = nBad = 0;
    while (m--) {
      int u;
      cin >> u;
      isGood[u] = true;
    }
    FOR(i, 1, n) {
      if (isGood[i]) {
        good[++nGood] = a[i];
      } else {
        bad[++nBad] = a[i];
      }
    }

    bool ok = true;
    FOR(i, 2, nGood) if (SZ(good[i]) != SZ(good[1])) {
      ok = false;
      break;
    }
    if (!ok) {
      cout << "No" << endl;
      continue;
    }

    string s = mostSpecific();
    FOR(i, 1, nBad) if (match(s, bad[i])) {
      ok = false;
      break;
    }
    if (!ok)
      cout << "No" << endl;
    else
      cout << "Yes\n" << s << endl;
  }
}
