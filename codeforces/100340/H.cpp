#include <bits/stdc++.h>
using namespace std;
const double oo = 1e15;

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

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (double k) { return Point(x*k, y*k); }
    Point operator / (double k) { return Point(x/k, y/k); }

    double operator * (Point a) { return x*a.x + y*a.y; } // dot product
    double operator % (Point a) { return x*a.y - y*a.x; } // cross product

    int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp

    Point conj() { return Point(x, -y); }
    double norm() { return x*x + y*y; }

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return sqrt(norm()); }

    Point rotate(double alpha) {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}
istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y;
    return cin;
}
ostream& operator << (ostream& cout, Point& p) {
    cout << p.x << ' ' << p.y;
    return cout;
}

double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}

double directed_angle(Point a, Point o, Point b) { // angle AOB, in range [0, 2*PI)
    double t = -atan2(a.y - o.y, a.x - o.x)
            + atan2(b.y - o.y, b.x - o.x);
    while (t < 0) t += 2*PI;
    return t;
}

// Distance from p to Line ab (closest Point --> c)
double distToLine(Point p, Point a, Point b, Point &c) {
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p-c).len();
}

// Distance from p to segment ab (closest Point --> c)
double distToLineSegment(Point p, Point a, Point b, Point &c) {
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
    Point A, B; // Added for polygon intersect line. Do not rely on assumption that these are valid
    Line() {}

    Line(double a, double b, double c) : a(a), b(b), c(c) {} 

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }
    Line(Point P, double m) {
        a = -m; b = 1;
        c = -((a * P.x) + (b * P.y));
    }
    double f(Point A) {
        return a*A.x + b*A.y + c;
    }
};

bool areParallel(Line l1, Line l2) {
    return cmp(l1.a*l2.b, l1.b*l2.a) == 0;
}

bool areSame(Line l1, Line l2) {
    return areParallel(l1 ,l2) && cmp(l1.c*l2.a, l2.c*l1.a) == 0
                && cmp(l1.c*l2.b, l1.b*l2.c) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;
    double dx = l1.b*l2.c - l2.b*l1.c;
    double dy = l1.c*l2.a - l2.c*l1.a;
    double d  = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}

bool between(Point a, Point b, Point c, int touch)
{
  return (a.x - b.x) * (a.x - c.x) < (touch ? EPS : -EPS)
      && (a.y - b.y) * (a.y - c.y) < (touch ? EPS : -EPS);
}

bool areCut(Line l1, Line l2, int touch = 0)
{
  Point p;
  if (!areIntersect(l1, l2, p))
    return 0;
  return between(p, l1.A, l1.B, touch) && between(p, l2.A, l2.B, touch);
}

int n, w, done[444];
Point a[444];
Line l[444];
double f[444], dist[444][444];

int isGood(Line cur)
{
  for (int i = 0; i < n * 2; i++)
    if (i % n != n - 1 && areCut(cur, l[i]))
      return 0;
  for (int i = 0; i < n; i++)
    if ((a[i].x - cur.A.x) * (a[i].x - cur.B.x) < EPS)
    {
      Line vertical(a[i], a[i + n]);
      if (!areParallel(cur, vertical) && !areCut(cur, vertical, 1))
        return 0;
    }
  return 1;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("race.in", "r", stdin);
  freopen("race.out", "w", stdout);
  cin >> n;
  for (int i = 0; i <= n; i++)
  {
    cin >> a[i].x >> a[i].y;
    if (i)
      l[i - 1] = Line(a[i], a[i - 1]);
  }
  n++;
  cin >> w;
  for (int i = 0; i < n; i++)
  {
    a[i + n].x = a[i].x;
    a[i + n].y = a[i].y + w;
    if (i)
      l[i + n - 1] = Line(a[i + n], a[i + n - 1]);
  }
  
  for (int i = 0; i < n * 2; i++)
  {
    if (i % n == 0)
    {
      f[i] = 0;
      continue;
    }
    int ok = a[i].y < a[n].y + EPS && a[i].y > a[0].y - EPS;
    Line cur(Point(0, a[i].y), a[i]);
    if (ok && isGood(cur)) f[i] = a[i].x;
    else f[i] = oo;
  }

  for (int i = 0; i < n * 2; i++)
    for (int j = i + 1; j < n * 2; j++)
      if (i != j)
      {
        if (isGood(Line(a[i], a[j]))) dist[i][j] = dist[j][i] = (a[i] - a[j]).len();
        else dist[i][j] = dist[j][i] = oo;
      }

  while (1)
  {
    double best = oo - 1;
    int u = -1;
    for (int i = 0; i < n * 2; i++)
      if (!done[i] && f[i] < best)
      {
        best = f[i];
        u = i;
      }
    if (u < 0) break;
    done[u] = 1;

    for (int v = 0; v < n * 2; v++)
      if (!done[v]) 
        f[v] = min(f[v], f[u] + dist[u][v]);
  }

  double ans = oo;
  for (int i = 0; i < n * 2; i++)
    if (done[i])
    {
      if (i % n == n - 1)
      {
        ans = min(ans, f[i]);
        continue;
      }

      int ok = a[i].y < a[2 * n - 1].y + EPS && a[i].y > a[n - 1].y - EPS;
      Line cur(Point(a[n - 1].x, a[i].y), a[i]);
      if (ok && isGood(cur))
        ans = min(ans, a[n - 1].x - a[i].x + f[i]);
    }

  cout << fixed << setprecision(12) << ans << endl;
}