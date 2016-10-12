
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

#define EPS 1e-6
const double PI = acos(-1.0);

double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

inline int cmp(double a, double b) {
  return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
  double x, y;
  Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

  Point operator+(const Point& a) const { return Point(x + a.x, y + a.y); }
  Point operator-(const Point& a) const { return Point(x - a.x, y - a.y); }
  Point operator*(double k) const { return Point(x * k, y * k); }
  Point operator/(double k) const { return Point(x / k, y / k); }

  double operator*(const Point& a) const {
    return x * a.x + y * a.y;
  }  // dot product
  double operator%(const Point& a) const {
    return x * a.y - y * a.x;
  }  // cross product

  int cmp(Point q) const {
    if (int t = ::cmp(x, q.x)) return t;
    return ::cmp(y, q.y);
  }

#define Comp(x) \
  bool operator x(Point q) const { return cmp(q) x 0; }
  Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
#undef Comp

      Point conj() {
    return Point(x, -y);
  }
  double norm() { return x * x + y * y; }

  // Note: There are 2 ways for implementing len():
  // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of
  // order X^2)
  // 2. hypot(x, y) --> slow, but much more accurate
  double len() { return sqrt(norm()); }

  Point rotate(double alpha) {
    double cosa = cos(alpha), sina = sin(alpha);
    return Point(x * cosa - y * sina, x * sina + y * cosa);
  }
};

int ccw(Point a, Point b, Point c) { return cmp((b - a) % (c - a), 0); }
int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));
istream& operator>>(istream& cin, Point& p) {
  cin >> p.x >> p.y;
  return cin;
}
ostream& operator<<(ostream& cout, Point& p) {
  cout << p.x << ' ' << p.y;
  return cout;
}

double angle(Point a, Point o, Point b) {  // min of directed angle AOB & BOA
  a = a - o;
  b = b - o;
  return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}

double directed_angle(Point a, Point o,
                      Point b) {  // angle AOB, in range [0, 2*PI)
  double t = -atan2(a.y - o.y, a.x - o.x) + atan2(b.y - o.y, b.x - o.x);
  while (t < 0) t += 2 * PI;
  return t;
}

// Distance from p to Line ab (closest Point --> c)
double distToLine(Point p, Point a, Point b, Point& c) {
  Point ap = p - a, ab = b - a;
  double u = (ap * ab) / ab.norm();
  c = a + (ab * u);
  return (p - c).len();
}

// Distance from p to segment ab (closest Point --> c)
double distToLineSegment(Point p, Point a, Point b, Point& c) {
  Point ap = p - a, ab = b - a;
  double u = (ap * ab) / ab.norm();
  if (u < 0.0) {
    c = Point(a.x, a.y);
    return (p - a).len();
  }
  if (u > 1.0) {
    c = Point(b.x, b.y);
    return (p - b).len();
  }
  return distToLine(p, a, b, c);
}

// NOTE: WILL NOT WORK WHEN a = b = 0.
struct Line {
  double a, b, c;
  Point A, B;  // Added for polygon intersect line. Do not rely on assumption
               // that these are valid

  Line(double a, double b, double c) : a(a), b(b), c(c) {}

  Line(Point A, Point B) : A(A), B(B) {
    a = B.y - A.y;
    b = A.x - B.x;
    c = -(a * A.x + b * A.y);
  }
  Line(Point P, double m) {
    a = -m;
    b = 1;
    c = -((a * P.x) + (b * P.y));
  }
  double f(Point A) { return a * A.x + b * A.y + c; }
};

bool areParallel(Line l1, Line l2) {
  return cmp(l1.a * l2.b, l1.b * l2.a) == 0;
}

bool areSame(Line l1, Line l2) {
  return areParallel(l1, l2) && cmp(l1.c * l2.a, l2.c * l1.a) == 0 &&
         cmp(l1.c * l2.b, l1.b * l2.c) == 0;
}

bool areIntersect(Line l1, Line l2, Point& p) {
  if (areParallel(l1, l2)) return false;
  double dx = l1.b * l2.c - l2.b * l1.c;
  double dy = l1.c * l2.a - l2.c * l1.a;
  double d = l1.a * l2.b - l2.a * l1.b;
  p = Point(dx / d, dy / d);
  return true;
}

void closestPoint(Line l, Point p, Point& ans) {
  if (fabs(l.b) < EPS) {
    ans.x = -(l.c) / l.a;
    ans.y = p.y;
    return;
  }
  if (fabs(l.a) < EPS) {
    ans.x = p.x;
    ans.y = -(l.c) / l.b;
    return;
  }
  Line perp(l.b, -l.a, -(l.b * p.x - l.a * p.y));
  areIntersect(l, perp, ans);
}

void reflectionPoint(Line l, Point p, Point& ans) {
  Point b;
  closestPoint(l, p, b);
  ans = p + (b - p) * 2;
}

struct Circle : Point {
  double r;
  Circle(double x = 0, double y = 0, double r = 0) : Point(x, y), r(r) {}
  Circle(Point p, double r) : Point(p), r(r) {}

  bool contains(Point p) { return (*this - p).len() <= r + EPS; }
};
bool areIntersect(Circle u, Circle v) {
  if (cmp((u - v).len(), u.r + v.r) > 0) return false;
  if (cmp((u - v).len() + v.r, u.r) < 0) return false;
  if (cmp((u - v).len() + u.r, v.r) < 0) return false;
  return true;
}

vector<Point> circleIntersect(Circle u, Circle v) {
  vector<Point> res;
  if (!areIntersect(u, v)) return res;
  double d = (u - v).len();
  double alpha = acos((u.r * u.r + d * d - v.r * v.r) / 2.0 / u.r / d);

  Point p1 = (v - u).rotate(alpha);
  Point p2 = (v - u).rotate(-alpha);
  res.push_back(p1 / p1.len() * u.r + u);
  res.push_back(p2 / p2.len() * u.r + u);
  return res;
}

Line go(Point A, Point B, Point other, double width) {
  Point dir;
  dir.x = B.y - A.y;
  dir.y = A.x - B.x;

  double len = dir.len();
  dir = dir * (width / len);

  Point AA = A + dir;
  Point BB = B + dir;
  if (ccw(A, B, AA) == ccw(A, B, other)) {
    AA = A - dir;
    BB = B - dir;
  }
  return Line(AA, BB);
}

int width;
void solve3(Point A, Point B, Point C) {
  Line ab = go(A, B, C, width);
  Line bc = go(B, C, A, width);
  Line ca = go(C, A, B, width);

  Point AA, BB, CC;
  assert(areIntersect(ab, ca, AA));
  assert(areIntersect(ab, bc, BB));
  assert(areIntersect(bc, ca, CC));

  cout << ((AA - BB).len() + (BB - CC).len() + (CC - AA).len()) << endl;
}

#undef int
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << (fixed) << setprecision(9);

  int AB, BC, CD, DA, AC;
  while (cin >> width >> AB >> BC >> CD >> DA >> AC) {
    assert(AB > 0 && BC > 0 && CD > 0 && DA > 0 && AC > 0);
    Point A(0, 0);
    Point C(AC, 0);

    Circle OA(A.x, A.y, AB);
    Circle OC(C.x, C.y, BC);
    auto t = circleIntersect(OA, OC);
    assert(SZ(t) > 0);
    Point B = t[0];
    if (B.y < 0) B = t[1];

    OA.r = DA;
    OC.r = CD;
    t = circleIntersect(OA, OC);
    assert(SZ(t) > 0);
    Point D = t[0];
    if (D.y > 0) D = t[1];

    /*
    DEBUG((A - B).len());
    DEBUG((B - C).len());
    DEBUG((C - D).len());
    DEBUG((D - A).len());
    DEBUG((A - C).len());
    */

    //    DEBUG(A);
    //    DEBUG(B);
    //    DEBUG(C);
    //    DEBUG(D);

    if (ccw(A, B, C) == 0) {
      solve3(A, C, D);
      continue;
    }
    if (ccw(B, C, D) == 0) {
      solve3(B, D, A);
      continue;
    }
    if (ccw(C, D, A) == 0) {
      solve3(C, A, B);
      continue;
    }
    if (ccw(D, A, B) == 0) {
      solve3(D, B, C);
      continue;
    }

    Line ab = go(A, B, C, width);
    Line bc = go(B, C, A, width);
    Line cd = go(C, D, A, width);
    Line da = go(D, A, B, width);

    Point AA, BB, CC, DD;
    assert(areIntersect(ab, da, AA));
    assert(areIntersect(ab, bc, BB));
    assert(areIntersect(bc, cd, CC));
    assert(areIntersect(cd, da, DD));

    cout << ((AA - BB).len() + (BB - CC).len() + (CC - DD).len() +
             (DD - AA).len())
         << endl;
  }
}
