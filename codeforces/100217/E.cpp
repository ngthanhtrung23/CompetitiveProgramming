#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
#define double long double
using namespace std;

const double EPS = 1e-11;
const double INF = 1e9;

int cmp(double x, double y) {
    if (fabs(x - y) < EPS) return 0;
    if (x < y) return -1;
    return 1;
}

// ------------------------ BASIC TYPE
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
} O(0.0), PI(acos((double) -1.0));

int cmp(const D& a, const D& b) {
    return cmp(a.x, b.x);
}

D sqrt(D x) { assert(x >= 0); return D(sqrt(x.x)); }
D abs(D x) { if (x < 0) return -x; else return x; }
D fabs(D x) { if (x < 0) return -x; else return x; }
D sin(D x) { return D(sin(x.x)); }
D cos(D x) { return D(cos(x.x)); }
D tan(D x) { return D(tan(x.x)); }
D asin(D x) { assert(D(-1) <= x && x <= D(1)); return asin(x.x); }
D acos(D x) { assert(D(-1) <= x && x <= D(1)); return acos(x.x); }
D atan(D x) { return D(atan(x.x)); }
D atan2(D x, D y) { return D(atan2(x.x, y.x)); }

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
    Point operator * (const D& k)     const { return Point(x*k, y*k); }
    Point operator / (const D& k)     const { assert(k != D(0)); return Point(x/k, y/k); }

    D operator * (const Point& a)     const { return x*a.x + y*a.y; } // dot
    D operator % (const Point& a)     const { return x*a.y - y*a.x; } // cross

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
D angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}
int ccw(const Point& a, const Point& b, const Point& c) {
    return ((b - a) % (c - a)).sign();
}

struct Line {
    D a, b, c;
    Point A, B;

    Line(D a, D b, D c) : a(a), b(b), c(c) {}

    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = D(0) - (a * A.x + b * A.y);
    }
    D f(const Point &p) {
        return a*p.x + b*p.y + c;
    }

    D dist(Point p) {
        return fabs(a*p.x + b*p.y + c) / sqrt(a*a + b*b);
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
    bool contains(Point p) {
        return (*this - p).len() <= r;
    }
};

// ------------------------ Line operations
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
    D d    = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}

// ------------------------ Circle operations
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
    if (d < -EPS)    return;
    d = sqrt(abs(d));
    Line l((c.x * r + c.y * d) / z,
            (c.y * r - c.x * d) / z,
            r1);
    ans.push_back(l);
}
// Actual method: returns vector containing all common tangents
vector<Line> commonTangents(Circle a, Circle b) {
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

// ------------------------ Polygon
typedef vector< Point > Polygon;

D area2(Point a, Point b, Point c) { return a%b + b%c + c%a; }
bool between(const Point &a, const Point &b, const Point &c) {
    return (fabs(area2(a,b,c)) < EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
void ConvexHull(vector<Point> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<Point> up, dn;
    for (int i = 0; i < pts.size(); i++) {
        while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
    
    if (pts.size() <= 2) return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < pts.size(); i++) {
        if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
}
D signed_area(Polygon p) {
    D area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}
D area(const Polygon &p) {
    return fabs(signed_area(p));
}

Circle a[555];
int n;

bool good(Line l) {
    // no circle intersect l
    FOR(i,1,n) if (l.dist(a[i]) < a[i].r) return false;

    // all circles are on same side
    int t = l.f(a[1]).sign();
    FOR(i,2,n) if (l.f(a[i]).sign() != t) return false;
    return true;
}

D directed_angle(Point a, Point o, Point b) { // angle AOB, in range [0, 2*PI)
    D t = -atan2(a.y - o.y, a.x - o.x)
            + atan2(b.y - o.y, b.x - o.x);
    while (t < 0) t = t + D(2.0) * PI;
    return t;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("murder.in", "r", stdin);
    freopen("murder.out", "w", stdout);
    cout << (fixed) << setprecision(9);

    while (cin >> n) {
        FOR(i,1,n) cin >> a[i].x >> a[i].y >> a[i].r;
        if (n == 1) {
            D res = PI * a[1].r * D(2.0);
            cout << res << endl;
            continue;
        }
        Polygon all;
        FOR(i,1,n) FOR(j,i+1,n) {
            auto tangents = commonTangents(a[i], a[j]);
            for(Line l : tangents) {
                if (l.f(a[i]).sign() != l.f(a[j]).sign()) continue;
                auto cur = intersection(l, a[i]);
                for(auto p : cur) all.push_back(p);
                cur = intersection(l, a[j]);
                for(auto p : cur) all.push_back(p);
            }
        }
        sort(all.begin(), all.end());
        all.resize(unique(all.begin(), all.end()) - all.begin());
        ConvexHull(all);

        D totalLen = D(0.0);
        REP(i,SZ(all)) {
            int j = (i+1) % SZ(all);
            int k = (j+1) % SZ(all);
            Line l(all[i], all[j]);

            int t = l.f(all[k]).sign();

            bool ok = true;
            FOR(x,1,n) if (l.dist(a[x]) < a[x].r) {
                ok = false;

                D alpha = angle(all[i], a[x], all[j]);
                if (l.f(a[x]).sign() != t) alpha = D(2.0) * PI - alpha;
                totalLen += alpha * a[x].r;
            }

            if (ok) totalLen += (all[i] - all[j]).len();
        }
        cout << totalLen << endl;
    }
}
