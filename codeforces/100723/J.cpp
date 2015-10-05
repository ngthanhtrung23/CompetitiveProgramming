
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
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

    void read() { cin >> x >> y; }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}

double angle(Point a, Point o, Point b) { // min of directed angle AOB & BOA
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * b.norm()));
}
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
bool in_polygon(const Polygon &P, Point pt) {
    if ((int)P.size() == 0) return false;
    double sum = 0;
    for (int i = 0; i < (int)P.size(); i++) {
        Point Pj = P[(i+1) % P.size()];
        // If allow on edge --> uncomment the following line
        // if (ccw(P[i], Pj, pt) == 0 && min(P[i], Pj) <= pt && pt <= max(P[i], Pj)) return true;
        if (ccw(pt, P[i], Pj) > 0)
            sum += angle(P[i], pt, Pj);
        else sum -= angle(P[i], pt, Pj);
    }
    return fabs(fabs(sum) - 2*acos(-1.0)) < EPS;
}

Polygon a[2511];
int h[2511];

struct Poly {
    double area;
    int id;
} x[2511];

bool operator < (const Poly& a, const Poly& b) {
    return a.area < b.area;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        FOR(i,1,n) {
            int k;
            cin >> h[i] >> k;
            a[i].resize(k);

            REP(j,k) a[i][j].read();
        }

        Point A(0, 0);
        Point B(100000, 0);

        FOR(i,1,n) {
            x[i].id = i;
            x[i].area = area(a[i]);
        }
        sort(x+1, x+n+1);

        int up = 0, down = 0;
        
        vector<int> left, right;
        FOR(i,1,n) {
            int id = x[i].id;
            bool ca = in_polygon(a[id], A);
            bool cb = in_polygon(a[id], B);

            if (ca && cb) continue;
            if (!ca && !cb) continue;

            if (ca) left.push_back(h[id]);
            else right.push_back(h[id]);
        }
        reverse(right.begin(), right.end());

        int ha = -1;
        for(int h : left) {
            if (ha < 0) ha = h;
            else if (ha < h) up += abs(h - ha);
            else down += abs(h - ha);

            ha = h;
        }
        for(int h : right) {
            if (ha < 0) ha = h;
            else if (ha < h) up += abs(h - ha);
            else down += abs(h - ha);

            ha = h;
        }
        cout << up << ' ' << down << '\n';
    }
}

