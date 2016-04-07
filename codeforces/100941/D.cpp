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
#define double long double
using namespace std;

#define EPS 1e-4
const double PI = acos(-1.0);

int GI(int& x) {
    return scanf("%lld", &x);
}

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

    void read() {
        int t;
        GI(t); x = t;
        GI(t); y = t;
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}
ostream& operator << (ostream& cout, Point& p) {
    cout << p.x << ' ' << p.y;
    return cout;
}
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
    double get(const double x) const {
        return (- c - a*x) / b;
    }
};
typedef vector< Point > Polygon;
double signed_area(Polygon p) {
    double area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}
double area(const Polygon &p) {
    return fabs(signed_area(p));
}

int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));

bool operator < (const Polygon& a, const Polygon& b) {
    return 0;
}

const int MN = 100111;
pair<double,Polygon> poly[MN];
int nPoly;

int nQuery;
Point query[MN];

bool good[MN];

#define Det(a,b,c) ((double)(b.x-a.x)*(double)(c.y-a.y)-(double)(b.y-a.y)*(c.x-a.x))
bool in_convex(vector<Point>& l, Point p){
    int a = 1, b = l.size()-1, c;
    if (Det(l[0], l[a], l[b]) > 0) swap(a,b);
    // Allow on edge --> if (Det... > 0 || Det ... < 0)
    if (Det(l[0], l[a], p) >= 0 || Det(l[0], l[b], p) <= 0) return false;
    while(abs(a-b) > 1) {
        c = (a+b)/2;
        if (Det(l[0], l[c], p) > 0) b = c; else a = c;
    }
    // Alow on edge --> return Det... <= 0
    return Det(l[a], l[b], p) < 0;
}

#undef int
int main() {
#define int long long
    freopen("castle.in", "r", stdin);
    freopen("castle.out", "w", stdout);
    cout << (fixed) << setprecision(9);

    while (GI(nPoly) == 1) {
        FOR(i,1,nPoly) {
            int k; GI(k);
            poly[i].second.resize(k);

            REP(j,k) poly[i].second[j].read();
            poly[i].first = area(poly[i].second);
        }
        sort(poly+1, poly+nPoly+1);
        GI(nQuery);
        FOR(i,1,nQuery) query[i].read();

        memset(good, 0, sizeof good);

        FOR(i,1,nQuery) {
            if (!in_convex(poly[nPoly].second, query[i])) continue;

            int l = 1, r = nPoly, res = nPoly;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (in_convex(poly[mid].second, query[i])) {
                    res = mid;
                    r = mid - 1;
                }
                else l = mid + 1;
            }

            good[res] = true;
        }
        double res = 0.0;
        FOR(i,1,nPoly) {
            if (good[i]) res += poly[i].first - poly[i-1].first;
        }
        cout << res << endl;
    }
}
