
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

int cnt[333];
char res[3][33];
bool ke[300][300];

void build() {
  memset(ke, 0, sizeof ke);
  FOR(i, 1, 2) FOR(j, 1, 13) {
    FOR(di, -1, 1) FOR(dj, -1, 1) if (di || dj) {
      int ii = i + di, jj = j + dj;
      if (ii > 0 && ii < 14 && jj > 0 && jj < 14) {
        ke[res[i][j]][res[ii][jj]] = 1;
      }
    }
  }
}

bool check(string s) {
  REP(i, SZ(s) - 1)
  if (!ke[s[i]][s[i + 1]]) return false;
  return true;
}

void print() {
  FOR(i, 1, 2) {
    FOR(j, 1, 13) cout << res[i][j];
    cout << endl;
  }
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  string s;
  while (cin >> s) {
    memset(cnt, 0, sizeof cnt);
    for (char c : s) ++cnt[c];
    char X;
    FOR(c, 'A', 'Z') if (cnt[c] == 2) X = c;
    string a = "", b = "", c = "";

    int i1 = -1, i2 = -1;
    REP(i, SZ(s)) if (s[i] == X) {
      if (i1 < 0)
        i1 = i;
      else
        i2 = i;
    }
    else {
      if (i1 < 0)
        a += s[i];
      else if (i2 < 0)
        b += s[i];
      else
        c += s[i];
    }
    //    DEBUG(a);
    //    DEBUG(b);
    //    DEBUG(c);

    int la = SZ(a), lb = SZ(b), lc = SZ(c);
    if (lb == 0) {
      cout << "Impossible" << endl;
      continue;
    }
    string all = b + c + a;
    bool ok = false;
    FOR(j, 1, 13) {
      res[1][j] = X;
      int i = 0;
      // right of X
      FOR(jj, j + 1, 13) res[1][jj] = all[i++];
      // second row
      FORD(jj, 13, 1) res[2][jj] = all[i++];
      // left of X
      FOR(jj, 1, j - 1) res[1][jj] = all[i++];

      build();
      if (check(s)) {
        print();
        ok = true;
        break;
      }
    }
    if (!ok) cout << "Impossible" << endl;
  }
}
