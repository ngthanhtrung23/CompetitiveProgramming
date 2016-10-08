
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
string s;
int k, n;
int a[MN], inc[MN];

void genInc(char c) {
  memset(inc, 0, sizeof inc);
  FOR(i,1,n) if (s[i] == c) {
    int l = max(1LL, i - k + 1);
    int r = min(n+1, i + 1);

    inc[l]++;
    inc[r]--;
  }
  FOR(i,1,n) inc[i] += inc[i-1];
}

bool can(char c) {
  genInc(c);
  FOR(i,1,n-k+1) if (a[i] + inc[i] == 0) return 0;
  return 1;
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  while (cin >> k >> s) {
    n = SZ(s);
    s = " " + s + " ";
    memset(a, 0, sizeof a);
    memset(inc, 0, sizeof inc);

    string res = "";
    FOR(c,'a','z') {
      if (can(c)) {
        vector<int> bad, good;
        FOR(i,1,n) {
          if (s[i] == c) good.push_back(i);
        }
        FOR(i,1,n-k+1) {
          if (a[i] == 0) bad.push_back(i);
        }
        int covered = 0;
        int i = 0, j = 0;
        while (i < SZ(bad)) {
          if (bad[i] > covered) {
            while (j + 1 < SZ(good) && bad[i] + k - 1 >= good[j+1]) ++j;
            covered = good[j];
            res += c;
          }
          ++i;
        }
        break;
      }
      genInc(c);
      FOR(i,1,n) a[i] += inc[i];
      FOR(i,1,n) if (s[i] == c) res += c;
    }
    cout << res << endl;
  }
}
