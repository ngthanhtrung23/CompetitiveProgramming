#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

#define sqr(x) ((x)*(x))
const long double eps = 1e-7;

struct Point {
    long double x, y;
    Point() {}
    Point(long double x, long double y) : x(x), y(y) {}
    
    Point operator - (Point a) { return Point(x - a.x, y - a.y); }
    Point operator + (Point a) { return Point(x + a.x, y + a.y); }
    Point operator / (long double k) { return Point(x / k, y / k); }
    
    long double len(Point v) { return sqrt(sqr(x-v.x) + sqr(y-v.y)); }
};

struct Line {
    long double a, b, c;
    Point A, B;
    Line() {}
    Line(Point A, Point B) : A(A), B(B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = - (a * A.x + b * A.y);
    }
};

struct Triangle {
    Point A, B, C;
} a[111];

long double res = 0.0;
int n;

Point gd[333];
int ngd;

bool operator == (Point A, Point B) {
    return (abs(A.x - B.x) < eps) && (abs(A.y - B.y) <= eps);
}

bool operator < (Point A, Point B) {
    if (A == B) return false;
    if (abs(A.x - B.x) < eps) return A.y < B.y;
    else return A.x < B.x;
}

int ccw(Point A, Point B, Point C) {
    C = C - A; B = B - A;
    long double t = B.x * C.y - B.y * C.x;
    if (abs(t) < eps) return 0;
    else if (t < 0) return -1;
    else return 1;
}

bool order(Point A, Point B, Point C) {
    int t = ccw(A, B, C);
    if (t) return false;
    if (B.x < min(A.x, C.x) - eps) return false;
    if (B.x > max(A.x, C.x) + eps) return false;
    if (B.y < min(A.y, C.y) - eps) return false;
    if (B.y > max(A.y, C.y) + eps) return false;
    return true;
}

bool intersect(Line x, Line y, Point &c) {
    long double dx = x.b*y.c - x.c*y.b;
    long double dy = x.c*y.a - x.a*y.c;
    long double d  = x.a*y.b - x.b*y.a;
    
    if (abs(d) < eps) return false;
    c = Point(dx/d, dy/d);
    
    if (!order(x.A, c, x.B)) return false;
    if (!order(y.A, c, y.B)) return false;
    return true;
}

bool inside(Point P, Triangle a) {
    if (ccw(a.A, a.B, P) * ccw(a.A, a.B, a.C) == -1) return false;
    if (ccw(a.B, a.C, P) * ccw(a.B, a.C, a.A) == -1) return false;
    if (ccw(a.C, a.A, P) * ccw(a.C, a.A, a.B) == -1) return false;
    return true;
}

bool check(Point u, Point v, int tri) {
    FOR(i,1,n)
        if (i != tri) if (inside((u+v)/2, a[i])) return false;
    return true;
}

void add(Point M, Point N, int tri) {
    Line x(M,N);
    ngd = 2;
    gd[0] = M;
    gd[1] = N;
    FOR(i,1,n)
    if (i != tri) {
        bool t; Point P;
        t = intersect(x, Line(a[i].A, a[i].B), P); if (t) gd[ngd++] = P;
        t = intersect(x, Line(a[i].B, a[i].C), P); if (t) gd[ngd++] = P;
        t = intersect(x, Line(a[i].C, a[i].A), P); if (t) gd[ngd++] = P;
    }
    sort(gd, gd + ngd);
    
    ngd = unique(gd, gd+ngd) - gd;
    
//    cout << M.x << ' ' << M.y << ' ' << N.x << ' ' << N.y << ' ' << tri << endl;
//    cout << ngd << ":  ";
//    REP(i,ngd) cout << gd[i].x << ' ' << gd[i].y << "  "; cout << endl;
    
    REP(i,ngd-1) {
        Point u = gd[i], v = gd[i+1];
        if (check(u,v,tri)) res += u.len(v);
    }
//    cout << res << endl;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i].A.x >> a[i].A.y;
        cin >> a[i].B.x >> a[i].B.y;
        cin >> a[i].C.x >> a[i].C.y;
    }
    
    FOR(i,1,n) {
        add(a[i].A, a[i].B, i);
        add(a[i].B, a[i].C, i);
        add(a[i].C, a[i].A, i);
    }
    double r = res;
    printf("%.10lf\n", r);
    return 0;
}
