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

int toInt(string t) {
  int h, m, s;
  sscanf(t.c_str(), "%lld:%lld:%lld", &h, &m, &s);
  return h * 3600 + m * 60 + s;
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);
  string tmp;
  double lastTime = 0, lastSpeed = 0;
  double totalDist = 0;
  while (getline(cin, tmp)) {
    while (tmp.back() == ' ') tmp.erase(SZ(tmp) - 1);
    while (tmp[0] == ' ') tmp.erase(0, 1);

    if (tmp.find(' ') != string::npos) {
      stringstream ss(tmp);
      string t;
      double speed;
      ss >> t >> speed;
      speed /= 3600.0;
      int time = toInt(t);
      totalDist += (time - lastTime) * lastSpeed;
      lastTime = time;
      lastSpeed = speed;
    } else {
      int time = toInt(tmp);
      cout << tmp << ' ' << setprecision(2)
           << totalDist + (time - lastTime) * lastSpeed << " km\n";
    }
  }
}
