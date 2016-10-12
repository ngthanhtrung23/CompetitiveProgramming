
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

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  int a, b;
  while (cin >> a >> b) {
    map<string, int> need, black, white;
    need["pawn"] = 8;
    need["rook"] = 2;
    need["knight"] = 2;
    need["bishop"] = 2;
    need["king"] = 1;
    need["queen"] = 1;

    int total = a;
    FOR(i, 1, a) {
      string c, name;
      cin >> c >> name;
      if (c == "black")
        black[name]++;
      else
        white[name]++;
    }
    vector<string> res;
    FOR(i, 1, b) {
      string c, name;
      cin >> c >> name;
      if (c == "black" && black[name] < need[name]) {
        black[name]++;
        total++;
        res.push_back(c + " " + name);
      } else if (c == "white" && white[name] < need[name]) {
        white[name]++;
        total++;
        res.push_back(c + " " + name);
      }
    }
    if (total < 32)
      cout << "impossible" << endl;
    else {
      for (auto s : res) cout << s << '\n';
    }
  }
}
