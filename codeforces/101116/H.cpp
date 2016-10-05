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

struct Point {
  int x, y;

  Point() {}
  Point(int x, int y) : x(x), y(y) {}

  Point operator-(const Point& a) const { return Point(x - a.x, y - a.y); }

  int operator%(const Point& a) const {
    return x * a.y - y * a.x;
  }  // cross product

  void read() { cin >> x >> y; }
} a[111];

int ccw(Point a, Point b, Point c) {
  int t = (b - a) % (c - a);
  assert(t);
  if (t < 0) return -1;
  return 1;
}
int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));

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
    FOR(i, 1, n) a[i].read();
    a[0] = a[n];
    a[n + 1] = a[1];
    a[n + 2] = a[2];

    int sum = 0;
    FOR(i, 1, n) {
      int j = i + 1;
      sum += a[i].x * a[j].y - a[j].x * a[i].y;
    }
    cout << ((sum > 0) ? "fight" : "run") << '\n';
  }
}
