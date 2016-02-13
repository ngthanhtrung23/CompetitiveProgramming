
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

const double EPS = 1e-9;
inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

struct Point {
    double x, y;
    int color;
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
struct Circle : Point {
    double r;
    Circle(double x = 0, double y = 0, double r = 0) : Point(x, y), r(r) {}
    Circle(Point p, double r) : Point(p), r(r) {}
    
    bool contains(Point p) { return (*this - p).len() <= r + EPS; }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}

Point a[333];
int n;
int black, white;

double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}

int l[333], r[333];
const double PI = acos((double) -1.0);

ostream& operator << (ostream& cout, Point& p) {
    cout << p.x << ' ' << p.y;
    return cout;
}
Circle getCircumcircle(Point a, Point b, Point c) {
    double d = 2.0 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    assert(fabs(d) > EPS);
    double x = (a.norm() * (b.y - c.y) + b.norm() * (c.y - a.y) + c.norm() * (a.y - b.y)) / d;
    double y = (a.norm() * (c.x - b.x) + b.norm() * (a.x - c.x) + c.norm() * (b.x - a.x)) / d;
    Point p(x, y);
    return Circle(p, (p - a).len());
}

bool order(Point a, Point b, Point c) {
    return (cmp(min(a.x, c.x), b.x) <= 0 && cmp(b.x, max(a.x, c.x)) <= 0
            && cmp(min(a.y, c.y), b.y) <= 0 && cmp(b.y, max(a.y, c.y)) <= 0);
}

bool check(Circle c) {
    int col1 = -1, col2 = -1;
    FOR(x,1,n) {
        double t = (a[x] - c).len();
        if (cmp(t, c.r) < 0) {
            if (col1 < 0) col1 = a[x].color;
            else if (col1 != a[x].color) return false;
        }
        if (cmp(t, c.r) > 0) {
            if (col2 < 0) col2 = a[x].color;
            else if (col2 != a[x].color) return false;
        }
        if (col1 >= 0 && col2 >= 0 && col1 == col2) return false;
    }
    cout << "YES" << endl;
    cout << c.x << ' ' << c.y << ' ' << c.r << endl;
    return true;
}

void solve() {
    FOR(i,1,n) FOR(j,i+1,n) FOR(k,j+1,n) if (ccw(a[i], a[j], a[k])) {
        Circle c = getCircumcircle(a[i], a[j], a[k]);

        if (check(c)) {
            return ;
        }
    }
    FOR(i,1,n) FOR(j,i+1,n) {
        Circle c;
        c.x = (a[i].x + a[j].x) / 2.0;
        c.y = (a[i].y + a[j].y) / 2.0;
        c.r = (a[i] - c).len();

        if (check(c)) {
            return ;
        }
    }
    cout << "NO" << endl;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("wall.in", "r", stdin);
    freopen("wall.out", "w", stdout);
    cout << (fixed) << setprecision(9);
    while (cin >> black >> white) {
        n = black + white;
        FOR(i,1,black) {
            cin >> a[i].x >> a[i].y;
            a[i].color = 0;
        }
        FOR(i,black+1,n) {
            cin >> a[i].x >> a[i].y;
            a[i].color = 1;
        }
        if (black == 1) {
            cout << a[1].x << ' ' << a[1].y << ' ' << 0 << endl;
            continue;
        }
        if (white == 1) {
            cout << a[n].x << ' ' << a[n].y << ' ' << 0 << endl;
            continue;
        }
        solve();
    }
}
