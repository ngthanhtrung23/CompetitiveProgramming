
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

    void read() {
        int t;
        GI(t); x = t;
        GI(t); y = t;
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}
int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(1, 1));
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
    double dx = l1.b*l2.c - l2.b*l1.c;
    double dy = l1.c*l2.a - l2.c*l1.a;
    double d  = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}

const int MN = 1000111;
const int oo = 1e9 + 0;
const int NANGLE = 3600 * 360;
pair<int,int> a[MN];
int na;

Point A(-oo, -oo);
Point B(+oo, -oo);
Point C(+oo, +oo);
Point D(-oo, +oo);

Line l1(A, B);
Line l2(B, C);
Line l3(C, D);
Line l4(D, A);

bool order(const Point& a, const Point& b, const Point& c) {
    return cmp(min(a.x, c.x), b.x) <= 0 && cmp(b.x, max(a.x, c.x)) <= 0
        && cmp(min(a.y, c.y), b.y) <= 0 && cmp(b.y, max(a.y, c.y)) <= 0;
}

double getId(Line l, Point p, Point x) {
    Point P;
    if (areIntersect(l, l1, P) && order(p, x, P) && order(A, P, B)) return P.x + oo;
    if (areIntersect(l, l2, P) && order(p, x, P) && order(B, P, C)) return P.y + 3*oo;
    if (areIntersect(l, l3, P) && order(p, x, P) && order(C, P, D)) return 5*oo - P.x;
    if (areIntersect(l, l4, P) && order(p, x, P) && order(D, P, A)) return 7*oo - P.y;
    return -1;
}

void addSegment(double l, double r) {
    ++na;
    a[na] = make_pair(
            floor(l + EPS),
            ceil(r - EPS)
            );
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;

    while (GI(n) == 1) {
        na = 0;
        FOR(i,1,n) {
            Point P; P.read();
            int diff; GI(diff);
            int alpha; GI(alpha);
            int beta = alpha + diff;

            Point X = Point(1, 0);
            X = X.rotate(alpha * 2 * PI / NANGLE) + P;
            Point Y = Point(1, 0);
            Y = Y.rotate(beta * 2 * PI / NANGLE) + P;

            Line px(P, X);
            Line py(P, Y);

            double id1 = getId(px, P, X);
            double id2 = getId(py, P, Y);

            if (cmp(id1, id2) > 0) {
                addSegment(id1, 8LL*oo);
                addSegment(0, id2);
            }
            else {
                addSegment(id1, id2);
            }
        }

//        FOR(i,1,na) cout << a[i].first << ' ' << a[i].second << endl;

        vector< pair<int,int> > events;
        FOR(i,1,na) {
            events.emplace_back(a[i].first, -1);
            events.emplace_back(a[i].second, +1);

            events.emplace_back(a[i].first + 8*oo, -1);
            events.emplace_back(a[i].second + 8*oo, 1);
        }
        sort(events.begin(), events.end());

        int opened = 0;
        int last = 0;
        int maxGap = -1, savel = -1, saver = -1;
        for(auto e : events) {
            if (e.second == -1) {
                if (!opened) {
                    // last --> e.first
                    int cur = e.first - last;
                    if (cur > maxGap) {
                        maxGap = cur;
                        saver = e.first;
                        savel = last;
                    }
                }
                ++opened;
            }
            else {
                --opened;
                last = e.first;
            }
        }
        if (maxGap <= 0) {
            cout << "NO" << endl;
            continue;
        }

        int t = (savel + saver) / 2;
        t %= 8*(int)(oo);

        cout << "YES" << endl;
        if (t <= 2*oo) {
            cout << t - oo << ' ' << -oo << endl;
        }
        else if (t <= 4*oo) {
            cout << oo << ' ' << t - 3*oo << ' ' << endl;
        }
        else if (t <= 6*oo) {
            cout << 5*oo - t << ' ' << oo << endl;
        }
        else {
            cout << -oo << ' ' << 7*oo - t << endl;
        }
        cout << endl;
    }
}
