
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

int n;
double X, Y;

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

struct Line {
    double a, b, c;
    Point A, B; // Added for polygon intersect line. Do not rely on assumption that these are valid

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

struct Circle : Point {
    double r;
    Circle(double x = 0, double y = 0, double r = 0) : Point(x, y), r(r) {}
    Circle(Point p, double r) : Point(p), r(r) {}
    
    bool contains(Point p) { return (*this - p).len() <= r + EPS; }
};

void tangents(Point c, double r1, double r2, vector<Line> & ans) {
    double r = r2 - r1;
    double z = sqr(c.x) + sqr(c.y);
    double d = z - sqr(r);
    if (d < -EPS)  return;
    d = sqrt(fabs(d));
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

vector<Point> intersection(Line l, Circle cir) {
    double r = cir.r, a = l.a, b = l.b, c = l.c + l.a*cir.x + l.b*cir.y;
    vector<Point> res;

    double x0 = -a*c/(a*a+b*b),  y0 = -b*c/(a*a+b*b);
    if (c*c > r*r*(a*a+b*b)+EPS) return res;
    else if (fabs(c*c - r*r*(a*a+b*b)) < EPS) {
        res.push_back(Point(x0, y0) + Point(cir.x, cir.y));
        return res;
    }
    else {
        double d = r*r - c*c/(a*a+b*b);
        double mult = sqrt (d / (a*a+b*b));
        double ax,ay,bx,by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;

        res.push_back(Point(ax, ay) + Point(cir.x, cir.y));
        res.push_back(Point(bx, by) + Point(cir.x, cir.y));
        return res;
    }
}

// ----------------------------------------------------------------------------------------------------
Circle a[22], b[22];
bool order(Point a, Point b, Point c) {
    return min(a.x, c.x) + EPS <= b.x && b.x <= max(a.x, c.x) - EPS
        && min(a.y, c.y) + EPS <= b.y && b.y <= max(a.y, c.y) - EPS;
}
bool check(Point p) {
    if (p.x < 0 || p.x > X || p.y < 0 || p.y > Y) return false;

    FOR(i,1,n) if (cmp((p - b[i]).len(), b[i].r) < 0) return false;
    FOR(i,1,n) {
        Circle pp;
        pp.x = p.x;
        pp.y = p.y;
        pp.r = 0.0;

        auto tt = tangents(pp, b[i]);
        for(auto t : tt) {
            auto td = intersection(t, b[i]) [0];

            FOR(j,1,n) if (j != i) {
                auto pp = intersection(t, b[j]);
                if (SZ(pp) == 2
                        && cmp(pp[0].x, pp[1].x) == 0
                        && cmp(pp[0].y, pp[1].y) == 0) continue;

                for(auto x : pp) {
                    if (order(p, x, td) || order(p, td, x)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

ostream& operator << (ostream& cout, Line& l) {
    cout << l.a << "*x + " << l.b << "*y + " << l.c << " = 0";
    return cout;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("zen.in", "r", stdin);
    freopen("zen.out", "w", stdout);
    while (cin >> n >> X >> Y) {
        FOR(i,1,n) {
            cin >> a[i].x >> a[i].y >> a[i].r;
            b[i] = a[i];
            b[i].r -= EPS;
        }
//        FOR(i,1,n) cout << 'C' << i << " = Circle[(" << a[i].x << ',' << a[i].y << "), " << a[i].r << "]\n";

        vector<Point> field;
        field.push_back(Point(0, 0));
        field.push_back(Point(X, 0));
        field.push_back(Point(X, Y));
        field.push_back(Point(0, Y));

        vector<Line> all;
        REP(i,4) {
            all.push_back(Line(field[i], field[(i+1) % 4]));
        }
        FOR(i,1,n) FOR(j,i+1,n) {
            auto tt = tangents(a[i], a[j]);
            for(auto t : tt) {
                if (t.f(a[i]) * t.f(a[j]) < 0) {
                    all.push_back(t);
                }
            }
        }

        try {
            REP(i,SZ(all)) FOR(j,i+1,SZ(all)-1) {
                Point p;
                if (areIntersect(all[i], all[j], p)) {
                    if (check(p)) {
                        cout << p.x << ' ' << p.y << endl;
                        throw 1;
                    }
                }
            }
            cout << "No Zen" << endl;
        } catch (int e) {
        }
    }
}
