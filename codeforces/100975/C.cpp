
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max(0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

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

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator * (double k) const { return Point(x*k, y*k); }
    Point operator / (double k) const { return Point(x/k, y/k); }

    double operator * (const Point& a) const { return x*a.x + y*a.y; } // dot product
    double operator % (const Point& a) const { return x*a.y - y*a.x; } // cross product

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
int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));
istream& operator >> (istream& cin, Point& p) {
    cin >> p.x >> p.y;
    return cin;
}
ostream& operator << (ostream& cout, Point& p) {
    cout << p.x << ' ' << p.y;
    return cout;
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
    double alpha = acos((u.r * u.r + d*d - v.r * v.r) / 2.0 / u.r / d);

    Point p1 = (v - u).rotate(alpha);
    Point p2 = (v - u).rotate(-alpha);
    res.push_back(p1 / p1.len() * u.r + u);
    res.push_back(p2 / p2.len() * u.r + u);
    return res;
}
Circle getCircumcircle(Point a, Point b, Point c) {
    double d = 2.0 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    assert(fabs(d) > EPS);
    double x = (a.norm() * (b.y - c.y) + b.norm() * (c.y - a.y) + c.norm() * (a.y - b.y)) / d;
    double y = (a.norm() * (c.x - b.x) + b.norm() * (a.x - c.x) + c.norm() * (b.x - a.x)) / d;
    Point p(x, y);
    return Circle(p, (p - a).len());
}

struct Arc {
    Point A, B, C;
    Circle O;

    bool contains(Point p) {
        if (cmp((p - O).len(), O.r)) return 0;
        if (A == p) return 1;
        if (B == p) return 1;
        
        return ccw(A, B, C) == ccw(A, B, p);
    }

    bool contains(Arc a) {
        return contains(a.A)
            && contains(a.B)
            && contains(a.C);
    }

    Point nearBoundary(int t) {
        const double E = 1e-6;
        if (t == 0) {
            Point p = (A - O).rotate(E) + O;
            if (!contains(p)) p = (A - O).rotate(-E) + O;
            assert(contains(p));
            
            return p;
        }
        else {
            Point p = (B - O).rotate(E) + O;
            if (!contains(p)) p = (B - O).rotate(-E) + O;
            assert(contains(p));

            return p;
        }
    }
} a[55];
int n;

istream& operator >> (istream& cin, Arc& x) {
    cin >> x.A >> x.B >> x.C;
    x.O = getCircumcircle(x.A, x.B, x.C);
    return cin;
}

vector<Point> intersectArc(Arc a, Arc b) {
    vector<Point> res;
    if (a.O == b.O) {
        if (a.A == b.A) res.push_back(a.A);
        if (a.A == b.B) res.push_back(a.A);
        if (a.B == b.A) res.push_back(a.B);
        if (a.B == b.B) res.push_back(a.B);
        return res;
    }

    auto pp = circleIntersect(a.O, b.O);
    for(auto p : pp) {
        if (a.contains(p) && b.contains(p)) res.push_back(p);
    }
    return res;
}

bool bad() {
    FOR(i,1,n) FOR(j,i+1,n) if (a[i].O == a[j].O) {
        if (a[i].contains(a[j])) return 1;
        if (a[j].contains(a[i])) return 1;

        if (a[i].A == a[j].A) continue;
        if (a[i].A == a[j].B) continue;
        if (a[i].B == a[j].A) continue;
        if (a[i].B == a[j].B) continue;

        Point AA = a[j].nearBoundary(0);
        Point BB = a[j].nearBoundary(1);

        if (a[i].contains(a[j].A) && a[i].contains(AA)) return 1;
        if (a[i].contains(a[j].B) && a[i].contains(BB)) return 1;
    }
    return 0;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("creativ.in", "r", stdin);
    freopen("creativ.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

//        FOR(i,1,n) {
//            cout << a[i].O << ": " << a[i].A << ' ' << a[i].B << ' ' << a[i].C << endl;
//        }
        if (bad()) cout << "Infinity" << endl;
        else {
            vector<Point> res;

            FOR(i,1,n) FOR(j,i+1,n) {
                auto p = intersectArc(a[i], a[j]);
                res.insert(res.end(), p.begin(), p.end());
            }

            sort(res.begin(), res.end());
            res.resize(unique(res.begin(), res.end()) - res.begin());
            cout << SZ(res) << '\n';
            for(auto p : res) cout << p << '\n';
        }
    }
}
