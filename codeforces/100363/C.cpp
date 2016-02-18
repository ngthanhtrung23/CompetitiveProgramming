
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
using namespace std;

const int MN = 155;
#define EPS 1e-6
const double PI = acos(-1.0);
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
    if (areSame(l1, l2)) return false;
    double dx = l1.b*l2.c - l2.b*l1.c;
    double dy = l1.c*l2.a - l2.c*l1.a;
    double d  = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}
int n;
Point a[MN];

bool check(Point p) {
    vector<double> x;
    FOR(i,1,n) {
        if (cmp(p.x, a[i].x) == 0 && cmp(p.y, a[i].y) == 0) return false;

        double dx = a[i].x - p.x;
        double dy = a[i].y - p.y;
        
        if (cmp(dy, 0) == 0) {
            x.push_back(atan2(0, 1));
        }
        else {
            if (dy < 0) dy = -dy, dx = -dx;
            x.push_back(atan2(dy, dx));
        }
    }
    sort(x.begin(), x.end());
    for(int i = 0; i < n; i += 2)
        if (cmp(x[i], x[i+1])) return false;
    for(int i = 1; i < n; i += 2)
        if (cmp(x[i], x[i+1]) == 0) return false;
    return true;
}

void solve() {
    int cnt = 0;
    Point save;
    FOR(i,2,n) {
        Line l1i(a[1], a[i]);

        int j = 2;
        while (j == i) ++j;

        FOR(k,j+1,n) {
            if (k == i) continue;

            Point p;
            if (areIntersect(l1i, Line(a[j], a[k]), p)) {
                if (check(p) && p != save) {
                    ++cnt;
                    if (cnt > 1) {
                        cout << "Ambiguity" << endl;
                        return ;
                    }
                    else save = p;
                }
            }
        }
    }
    if (cnt == 0) cout << "Impossible" << endl;
    else cout << "Center of the universe found at (" << save.x << ", " << save.y << ")" << endl;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("center.in", "r", stdin);
    freopen("center.out", "w", stdout);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        n *= 2;
        FOR(i,1,n) cin >> a[i];
        solve();
    }
}
