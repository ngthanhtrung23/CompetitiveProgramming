#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

#define EPS 1e-6

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

    double operator % (Point a) { return x*a.y - y*a.x; } // cross product
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}

struct Line {
    double a, b, c;
    Point A, B; // Added for polygon intersect line. Do not rely on assumption that these are valid

    Line(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {
        if (cmp(b, 0) == 0) {
            A = Point(-c/a, 0);
            B = Point(-c/a, 1);
        }
        else {
            A = Point(0, -c/b);
            B = Point(1, (-c-a)/b);
        }
    } 

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
} lines[111];
typedef vector< Point > Polygon;

bool areParallel(Line l1, Line l2) {
    return cmp(l1.a*l2.b, l1.b*l2.a) == 0;
}
bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;
    double dx = l1.b*l2.c - l2.b*l1.c;
    double dy = l1.c*l2.a - l2.c*l1.a;
    double d  = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}
Polygon polygon_cut(const Polygon& P, const Line& l) {
    Polygon Q;
    for(int i = 0; i < P.size(); ++i) {
        Point A = P[i], B = (i == P.size()-1) ? P[0] : P[i+1];
        if (ccw(l.A, l.B, A) != -1) Q.push_back(A);
        if (ccw(l.A, l.B, A)*ccw(l.A, l.B, B) < 0) {
            Point p; areIntersect(Line(A, B), l, p);
            Q.push_back(p);
        }
    }
    return Q;
}

int nLine, nPoint;

vector< pair<Polygon, Polygon> > all[111];
const double oo = 1.2e9;

Point get_center(const Polygon& p) {
    Point res = Point(0, 0);
    for(auto x : p)
        res = res + x;
    return res / p.size();
}

int main() {
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        scanf("%d%d", &nLine, &nPoint);
        FOR(i,1,nLine) {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            lines[i] = Line(a, b, c);
        }

        FOR(i,0,nLine) all[i].clear();
        Polygon space;
        space.push_back(Point(-oo,-oo));
        space.push_back(Point(-oo, oo));
        space.push_back(Point( oo, oo));
        space.push_back(Point( oo,-oo));
        Polygon a;
        FOR(i,1,nPoint) {
            int x, y; scanf("%d%d", &x, &y);
            a.push_back(Point(x, y));
        }

        all[0].push_back(make_pair(space, a));
        bool bad = false;
        FOR(i,1,nLine) {
            for(auto x : all[i-1]) {
                Polygon p = x.first;
                Polygon knights = x.second;

                Polygon left = polygon_cut(p, lines[i]);
                swap(lines[i].A, lines[i].B);
                Polygon right = polygon_cut(p, lines[i]);
                swap(lines[i].A, lines[i].B);

                if (left.empty() || right.empty()) {
                    all[i].push_back(x);
                }
                else {
                    Point center_left = get_center(left);
                    Point center_right = get_center(right);

                    int sign_left = cmp(lines[i].f(center_left), 0);
                    Polygon k_left, k_right;

                    for(auto k : knights) {
                        int sign = cmp(lines[i].f(k), 0);
                        if (sign == sign_left) k_left.push_back(k);
                        else k_right.push_back(k);
                    }

                    if (k_left.empty() || k_right.empty()) {
                        bad = true;
                        break;
                    }

                    all[i].push_back(make_pair(left, k_left));
                    all[i].push_back(make_pair(right, k_right));
                }
            }
            if (bad) break;
        }
        if (bad) puts("VULNERABLE"); else puts("PROTECTED");
    }
    return 0;
}
