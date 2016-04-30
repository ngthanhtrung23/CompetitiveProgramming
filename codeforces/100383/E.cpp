#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A,n)  { cerr << #A << " = "; FOR(_,1,n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A,n) { cerr << #A << " = "; REP(_,n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max(0.0,x));
}
int GI(int& x) {
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
//    cout << '(' << p.x << ',' << p.y << ')';
    cout << p.x << ' ' << p.y;
    return cout;
}

double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
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

Point a[111];
double ALPHA = 1.5e-4;
double x[111];

bool check(int n) {
    a[0] = a[n];
    a[n+1] = a[1];
    a[n+2] = a[2];

    int dir = ccw(a[0], a[1], a[2]);

    FOR(i,1,n) {
        double alpha = angle(a[i-1], a[i], a[i+1]);
        FOR(j,1,n) if (j != i) {
            double beta = angle(a[j-1], a[j], a[j+1]);
            if (fabs(alpha - beta) <= 1e-4) {
                return 0;
            }
        }

        if (ccw(a[i-1], a[i], a[i+1]) != dir) return 0;

        double len = (a[i] - a[i+1]).len();
        if (fabs(len - 1) > 1e-8) return 0;
    }
    return 1;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(16);
//    srand(7777);

    int n;
    while (cin >> n) {
        if (n == 5) {
            cout << "1.0000000000000000 1.0000000000000000" << endl;
            cout << "2.0000000000000000 1.0000000000000000" << endl;
            cout << "2.3093247548365476 1.9509564638012140" << endl;
            cout << "1.5003804226047008 2.5388417139563542" << endl;
            cout << "0.6912907818637410 1.9511564638048255" << endl;
            continue;
        }
        double each = ((n - 2) * PI) / (double) n;

        a[1] = Point(0, 0);
        a[2] = Point(1, 0);

        bool found = 0;

        REP(rot,3) {
            double DIV;
            if (rot == 0) DIV = 2.05;
            else if (rot == 1) DIV = 2.07;
            else DIV = 2.1;

            int nAngle = n-2;
            FOR(i,1,nAngle) {
                if (i == 1) x[1] = each + ALPHA * n/DIV;
                else x[i] = x[i-1] - ALPHA;
            }

            REP(turn,100) {
                bool bad = true;
                reverse(x+2, x+nAngle+1);
                int iteration = 0;
                while (bad) {
                    ++iteration;
                    if (iteration > 1000) break;
                    bad = false;
                    random_shuffle(x+4, x+nAngle+1);

                    FOR(i,3,n) {
                        double cur = x[i-2];
                        a[i] = (a[i-2] - a[i-1]).rotate(cur) + a[i-1];
                    }
                    a[0] = a[n];
                    a[n+1] = a[1];
                    a[n+2] = a[2];


                    int dir = ccw(a[0], a[1], a[2]);
                    FOR(i,1,n) {
                        if (ccw(a[i-1], a[i], a[i+1]) != dir) {
                            bad = true;
                        }
                    }
                    if (bad) continue;

                    double ln = 0.0;
                    double nn = 2.0;
                    FOR(i,1,n) {
                        double cur = (a[i] - a[i+1]).len();
                        ln = max(ln, cur);
                        nn = min(nn, cur);
                    }
                    if (ln > 1 + 1e-3) {
                        bad = true;
                        continue;
                    }
                }
                Circle cn; cn.x = a[n].x; cn.y = a[n].y; cn.r = 1.0;
                Circle c2; c2.x = a[2].x; c2.y = a[2].y; c2.r = 1.0;
                if (check(n)) {
                    found = true;
                    continue;
                }

                if (!(areIntersect(c2, cn))) {
                    continue;
                }


                auto pp = circleIntersect(cn, c2);
                found = 0;
                for(auto p : pp) {
                    a[1] = p;
                    if (check(n)) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) break;
        }

        if (!check(n)) {
            double ln = 0.0;
            double nn = 2.0;
            FOR(i,1,n) {
                double cur = (a[i] - a[i+1]).len();
                ln = max(ln, cur);
                nn = min(nn, cur);
            }
            DEBUG(n);
        }
        else {
            FOR(i,1,n) cout << a[i] << endl;
        }
    }
}
