
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define double long double
#define SZ(x) ((int) (x).size())
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define sqr(x) ((x) * (x))
using namespace std;

const double EPS = 1e-6;
const double INF = 1e9;
int cmp(double x, double y) {
  if (fabs(x - y) < EPS) return 0;
  if (x < y) return -1;
  return 1;
}

struct D {
  double x;

  D() {}
  D(double x) : x(x) {}

  D operator + (const D& a) const { return D(x+a.x); }
  D operator - (const D& a) const { return D(x-a.x); }
  D operator * (const D& a) const { return D(x*a.x); }
  D operator / (const D& a) const { return D(x/a.x); }

  D operator - () const { return D(-x); }

  D& operator += (const D& a) { return *this = *this + a; }
  D& operator -= (const D& a) { return *this = *this - a; }
  D& operator *= (const D& a) { return *this = *this * a; }
  D& operator /= (const D& a) { return *this = *this / a; }

  bool operator == (const D& a) const { return cmp(x, a.x) == 0; }
  bool operator <= (const D& a) const { return cmp(x, a.x) <= 0; }
  bool operator >= (const D& a) const { return cmp(x, a.x) >= 0; }
  bool operator <  (const D& a) const { return cmp(x, a.x) <  0; }
  bool operator >  (const D& a) const { return cmp(x, a.x) >  0; }
  bool operator != (const D& a) const { return cmp(x, a.x) != 0; }

  int sign() {
    int t = cmp(x, 0);
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
  }

  friend istream& operator >> (istream& cin, D& x) {
    cin >> x.x;
    return cin;
  }
  friend ostream& operator << (ostream& cout, D& x) {
    cout << x.x;
    return cout;
  }
};

int cmp(const D& a, const D& b) {
  return cmp(a.x, b.x);
}

D sqrt(D x) { assert(x >= 0); return D(sqrt(x.x)); }
D abs(D x) { if (x < 0) return -x; else return x; }
D cos(D x) { return cos(x.x); }
D sin(D x) { return sin(x.x); }
D acos(D x) { assert(D(-1) <= x && x <= D(1)); return acos(x.x); }
D asin(D x) { assert(D(-1) <= x && x <= D(1)); return asin(x.x); }

struct Point {
  D x, y;

  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  Point(D x, D y) : x(x), y(y) {}

  int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

  #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
  Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
  #undef Comp

  Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
  Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
  Point operator * (const D& k) const { return Point(x*k, y*k); }
  Point operator / (const D& k) const { assert(k != D(0)); return Point(x/k, y/k); }

  D operator * (const Point& a) const { return x*a.x + y*a.y; } // dot
  D operator % (const Point& a) const { return x*a.y - y*a.x; } // cross

  friend istream& operator >> (istream& cin, Point& a) {
    cin >> a.x >> a.y;
    return cin;
  }
  friend ostream& operator << (ostream& cout, Point& a) {
    cout << a.x << ' ' << a.y;
    return cout;
  }

  D norm() { return x*x + y*y; }
  D len() { return hypot(x.x, y.x); }

  Point rotate(D alpha) {
    D cosa = cos(alpha), sina = sin(alpha);
    return Point(x * cosa - y * sina, x * sina + y * cosa);
  }

  Point normalize(D l) {
    return Point(x, y) * l / len();
  }
};

struct Line {
  D a, b, c;
  Point A, B;

  Line(D a, D b, D c) : a(a), b(b), c(c) {}

  Line(Point A, Point B) : A(A), B(B) {
    a = B.y - A.y;
    b = A.x - B.x;
    c = D(0) - (a * A.x + b * A.y);
  }
};

struct Circle : Point {
  D r;

  Circle() {}
  Circle(Point a, D r) : Point(a), r(r) {}

  bool strictContains(Point p) {
    return (*this - p).len() < r;
  }

  bool onBorder(Point p) {
    return (*this - p).len() == r;
  }
};

bool areParallel(Line l1, Line l2) {
  return l1.a*l2.b == l1.b*l2.a;
}

bool areSame(Line l1, Line l2) {
  return areParallel(l1 ,l2) && l1.c*l2.a == l2.c*l1.a
        && l1.c*l2.b == l1.b*l2.c;
}

bool areIntersect(Line l1, Line l2, Point &p) {
  if (areParallel(l1, l2)) return false;
  D dx = l1.b*l2.c - l2.b*l1.c;
  D dy = l1.c*l2.a - l2.c*l1.a;
  D d  = l1.a*l2.b - l2.a*l1.b;
  p = Point(dx/d, dy/d);
  return true;
}

bool areIntersect(Circle u, Circle v) {
  if (cmp((u - v).len(), u.r + v.r) > 0) return false;
  if (cmp((u - v).len() + v.r, u.r) < 0) return false;
  if (cmp((u - v).len() + u.r, v.r) < 0) return false;
  return true;
}

vector<Point> circleIntersect(Circle u, Circle v) {
  vector<Point> res;
  if (!areIntersect(u, v)) return res;
  D d = (u - v).len();
  D alpha = acos((u.r * u.r + d*d - v.r * v.r) / 2.0 / u.r / d);

  Point p1 = (v - u).rotate(alpha);
  Point p2 = (v - u).rotate(-alpha);
  res.push_back(p1 / p1.len() * u.r + u);
  res.push_back(p2 / p2.len() * u.r + u);
  return res;
}

// Circle & line intersection
vector<Point> intersection(Line l, Circle cir) {
  D r = cir.r, a = l.a, b = l.b, c = l.c + l.a*cir.x + l.b*cir.y;
  vector<Point> res;

  D x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
  if (c*c > r*r*(a*a+b*b)) return res;
  else if (c*c == r*r*(a*a+b*b)) {
    res.push_back(Point(x0, y0) + Point(cir.x, cir.y));
    return res;
  }
  else {
    D d = r*r - c*c/(a*a+b*b);
    D mult = sqrt (d / (a*a+b*b));
    D ax,ay,bx,by;
    ax = x0 + b * mult;
    bx = x0 - b * mult;
    ay = y0 - a * mult;
    by = y0 + a * mult;

    res.push_back(Point(ax, ay) + Point(cir.x, cir.y));
    res.push_back(Point(bx, by) + Point(cir.x, cir.y));
    return res;
  }
}

// Find common tangents to 2 circles
// Helper method
void tangents(Point c, D r1, D r2, vector<Line> & ans) {
  D r = r2 - r1;
  D z = sqr(c.x) + sqr(c.y);
  D d = z - sqr(r);
  if (d < -EPS)  return;
  d = sqrt(abs(d));
  Line l((c.x * r + c.y * d) / z,
      (c.y * r - c.x * d) / z,
      r1);
  ans.push_back(l);
}
// Actual method: returns vector containing all common tangents
vector<Line> tangents(Circle a, Circle b) {
  vector<Line> ans; ans.clear();
  for (int i=-1; i<=1; i+=2)
    for (int j=-1; j<=1; j+=2)
      tangents(b-a, a.r*i, b.r*j, ans);
  for(int i = 0; i < ans.size(); ++i)
    ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;

  vector<Line> ret;
  for(int i = 0; i < (int) ans.size(); ++i) {
    bool ok = true;
    for(int j = 0; j < i; ++j)
      if (areSame(ret[j], ans[i])) {
        ok = false;
        break;
      }
    if (ok) ret.push_back(ans[i]);
  }
  return ret;
}

int ccw(const Point& a, const Point& b, const Point& c) {
	return ((b - a) % (c - a)).sign();
}

int nPole, n;
Point start, target;
Circle poles[11];
Point a[2011];
D f[2011], c[2011][2011];

bool strictBetween(Point a, Point b, Point c) {
  assert(ccw(a, b, c) == 0);
  return MIN(a, c) < b && b < MAX(a, c);
}

D angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
  a = a - o; b = b - o;
  return acos((a * b) / sqrt(a.norm() * b.norm()));
}

bool block(const Point& p) {
  FOR(i,1,nPole) if (poles[i].strictContains(p)) return true;
  return false;
}

int main() {
  ios :: sync_with_stdio(0); cin.tie(0);
  cout << (fixed) << setprecision(9);
  while (cin >> nPole >> target) {
    start = Point(0, 0);
    FOR(i,1,nPole) {
      Point t; cin >> t;
      poles[i] = Circle(t, 100);
    }

    int s = 1; a[1] = start;
    int t = 2; a[2] = target;
    if (block(start) || block(target)) {
      cout << 0.0 << endl;
      continue;
    }
    n = 2;
    // tangents from start & target to all poles
    REP(turn,2) {
      FOR(i,1,nPole) {
        Point from;
        if (turn == 0) from = start; else from = target;

        vector<Line> t = tangents(Circle(from, D(0)), poles[i]);
        for(auto l : t) {
          auto ps = intersection(l, poles[i]);
          for(auto p : ps) if (!block(p)) {
            a[++n] = p;
          }
        }
      }
    }
    // tangents between 2 circles
    FOR(i,1,nPole) FOR(j,i+1,nPole) {
      vector<Line> t = tangents(poles[i], poles[j]);
      for(auto l : t) {
        auto ps = intersection(l, poles[i]);
        for(auto p : ps) if (!block(p)) {
          a[++n] = p;
        }
        ps = intersection(l, poles[j]);
        for(auto p : ps) if (!block(p)) {
          a[++n] = p;
        }
      }
    }

    FOR(i,1,n) FOR(j,1,n) {
      if (i == j) c[i][j] = 0;
      else {
        c[i][j] = INF;

        // Connect with straight line
        Line l(a[i], a[j]);

        bool ok = true;
        FOR(poleId,1,nPole) {
          if (poles[poleId].strictContains(a[i])
              || poles[poleId].strictContains(a[j])) {
            ok = false;
            break;
          }
          if (poles[poleId].onBorder(a[i]) && poles[poleId].onBorder(a[j])) {
            ok = false;
            break;
          }
          vector<Point> t = intersection(l, poles[poleId]);
          for(auto p : t) {
            if (ccw(a[i], p, a[j]) == 0
                && strictBetween(a[i], p, a[j])) {
              ok = false;
            }
          }
        }
        if (ok) {
          // segment i - j does not intersect with any poles
          c[i][j] = (a[i] - a[j]).len();
          continue;
        }

        // Connect with circle arc
        FOR(p1,1,nPole) {
          if (poles[p1].onBorder(a[i])
              && poles[p1].onBorder(a[j])) {
            // the 2 points are on this circle
            int canPos = true, canNeg = true;
            FOR(p2,1,nPole) if (p2 != p1) {
              if (poles[p2].strictContains(a[i])
                  || poles[p1].strictContains(a[j])) {
                canPos = canNeg = false;
                break;
              }
              auto ps = circleIntersect(poles[p1], poles[p2]);
              if (SZ(ps) == 2) {
                if ((ps[0] == a[i] && ps[1] == a[j])
                    || (ps[0] == a[j] && ps[1] == a[i])) {
                  if (ccw(a[i], a[j], poles[p2]) < 0) canNeg = false;
                  else canPos = false;
                }
              }
              for(auto p : ps) {
                if (p == a[i] || p == a[j]) continue;
                int t = ccw(a[i], a[j], p);
                if (t < 0) canNeg = false;
                if (t > 0) canPos = false;
              }
            }

            D alpha = angle(a[i], poles[p1], a[j]);
            D l1 = alpha * 100.0;
            D l2 = (D(2.0*acos(-1.0)) - alpha) * 100.0;

            D posLen = D(INF), negLen = D(INF);
            if (ccw(a[i], poles[p1], a[j]) == 0) {
              posLen = l1;
              negLen = l2;
            }
            else {
              Point x = (a[i] + a[j]) * 0.5;
              Point dir = (x - poles[p1]).normalize(100);
              Point mid = poles[p1] + (x - poles[p1]).normalize(100);
              if (ccw(a[i], a[j], mid) > 0) {
                posLen = l1;
                negLen = l2;
              }
              else {
                posLen = l2;
                negLen = l1;
              }
            }

            if (canPos) c[i][j] = MIN(c[i][j], posLen);
            if (canNeg) c[i][j] = MIN(c[i][j], negLen);
          }
        }
      }
    }
    FOR(k,1,n)
      FOR(i,1,n) FOR(j,1,n)
        c[i][j] = MIN(c[i][j], c[i][k] + c[k][j]);
    if (c[1][2] > 1e8) cout << 0.0 << endl;
    else cout << c[1][2] << endl;
  }
}
