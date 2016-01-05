
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

#define double long double
const double EPS = 1e-12;
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
D sin(D x) { return sin(x.x); }
D cos(D x) { return cos(x.x); }
D tan(D x) { return tan(x.x); }
D asin(D x) { assert(D(-1) <= x && x <= D(1)); return asin(x.x); }
D acos(D x) { assert(D(-1) <= x && x <= D(1)); return acos(x.x); }
D atan(D x) { return atan(x.x); }

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

int n;
int nTower;
Circle towers[111];
Point a[1011];
D c[1011][1011];
D R;

bool isGood(const Point& p) {
    FOR(i,1,nTower)
        if ((towers[i] - p).len() < R) return false;
    return true;
}

D segment_union(vector< pair<D, D> > segs) {
    int n = SZ(segs);
    vector< pair<D, bool> > x(n*2);
    REP(i,n) {
        x[i*2] = make_pair(segs[i].first, false);
        x[i*2+1] = make_pair(segs[i].second, true);
    }
    sort(x.begin(), x.end());

    D res = 0.0;
    int c = 0;
    REP(i,n*2) {
        if (c && i) res += x[i].first - x[i-1].first;
        if (x[i].second) ++c;
        else --c;
    }
    return res;
}

bool isGood(Point a, Point b) {
    if (a > b) swap(a, b);

    vector< pair<D, D> > segs;
    Line l(a, b);

    D a_b = (b - a).len();

    FOR(i,1,nTower) {
        auto t = intersection(l, towers[i]);
        if (SZ(t) < 2) continue;

        D x, y;
        if (t[0] >= a) x = (t[0] - a).len();
        else x = D(0);

        if (x > a_b) x = a_b;

        if (t[1] >= a) y = (t[1] - a).len();
        else y = D(0);

        if (y > a_b) y = a_b;

        segs.push_back(make_pair(min(x, y), max(x, y)));
    }
    return segment_union(segs) == a_b;
}

D f[1011];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(12);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> R;
        cin >> nTower;

        Point start, target; cin >> start >> target;

        FOR(i,1,nTower) {
            cin >> towers[i];
            towers[i].r = R;
        }

//        cout << "towers: " << endl;
//        FOR(i,1,nTower) cout << towers[i] << ' ' << endl;

        n = 0;
        FOR(i,1,nTower) {
            FOR(j,i+1,nTower) {
                auto v = circleIntersect(towers[i], towers[j]);
                for(auto p : v) if (isGood(p)) {
                    a[++n] = p;
                }
            }
        }
        sort(a+1, a+n+1);
        n = unique(a+1, a+n+1) - a - 1;
        a[++n] = start;
        a[++n] = target;

        if (n > 1000) continue;

//        cout << "Interesting points: " << endl;
//        FOR(i,1,n) cout << a[i] << endl;

        FOR(i,1,n) FOR(j,i+1,n) {
            if (isGood(a[i], a[j])) {
                c[i][j] = c[j][i] = (a[i] - a[j]).len();
//                cout << i << " --> " << j << endl;
            }
            else {
                c[i][j] = c[j][i] = 1e9;
            }
        }
        set< pair<D, int> > all;
        FOR(i,1,n) f[i] = D(INF);
        f[n-1] = D(0.0);
        all.insert(make_pair(f[n-1], n-1));
        while (!all.empty()) {
            auto p = *all.begin(); all.erase(all.begin());
            int u = p.second;
            D cur = p.first;
            if (cur != f[u]) continue;

            if (u == n) break;

            FOR(v,1,n) if (f[v] > f[u] + c[u][v]) {
                f[v] = f[u] + c[u][v];
                all.insert(make_pair(f[v], v));
            }
        }
        if (f[n] == D(INF)) f[n] = -1;
//        PR(f, n);
        cout << f[n] << '\n';
    }
}
