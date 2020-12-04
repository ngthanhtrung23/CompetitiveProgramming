#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

int rand16() {
    return rand() & (TWO(16) - 1);
}
int my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

int GI(int& x) { return scanf("%lld", &x); }

int cmp(int x, int y) {
    if (x == y) return 0;
    if (x < y) return -1;
    return 1;
}

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }

    int operator * (const Point& a) const { return x*a.x + y*a.y; } // dot product
    int operator % (const Point& a) const { return x*a.y - y*a.x; } // cross product

    int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp
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
    cout << '(' << p.x << ',' << p.y << ')';
    return cout;
}

typedef vector< Point > Polygon;

int area2(Point a, Point b, Point c) { return a%b + b%c + c%a; }
#define REMOVE_REDUNDANT
#ifdef REMOVE_REDUNDANT
bool between(const Point &a, const Point &b, const Point &c) {
    return (area2(a,b,c) == 0 && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
#endif

void ConvexHull(vector<Point> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<Point> up, dn;
    for (int i = 0; i < SZ(pts); i++) {
        while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
    
#ifdef REMOVE_REDUNDANT
    if (pts.size() <= 2) return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < SZ(pts); i++) {
        if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
#endif
}

#define Det(a,b,c) ((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x))
const int OUTSIDE = 0;
const int ON_EDGE = 1;
const int INSIDE = 2;
int in_convex(const vector<Point>& l, Point p){
    // Check if point is on edge.
    int n = SZ(l);
    REP(i,n) {
        int j = (i + 1) % n;
        Point u = l[i], v = l[j];

        if (u > v) swap(u, v);

        if (ccw(u, v, p) == 0 && u <= p && p <= v) return ON_EDGE;
    }

    int a = 1, b = l.size()-1, c;
    if (Det(l[0], l[a], l[b]) > 0) swap(a,b);
    // Allow on edge --> if (Det... > 0 || Det ... < 0)
    if (Det(l[0], l[a], p) > 0 || Det(l[0], l[b], p) < 0) return OUTSIDE;
    while(abs(a-b) > 1) {
        c = (a+b)/2;
        if (Det(l[0], l[c], p) > 0) b = c; else a = c;
    }
    // Alow on edge --> return Det... <= 0
    return (Det(l[a], l[b], p) <= 0) ? INSIDE : OUTSIDE;
}

int count_in_hull(const Polygon& green, const Polygon& hull) {
    int res = 0;
    for (auto P : green) {
        if (in_convex(hull, P)) {
            ++res;
        }
    }
    return res;
}

bool in_segment(Point a, Point b, Point c) {
    if (b > c) swap(b, c);
    return ccw(b, a, c) == 0 && b < a && a < c;
}

bool can(Point green, Point p0, Point p1, const Polygon& a12, const Polygon& a20) {
    for (auto x : a12)
        for (auto y : a20)
            if (in_convex(vector<Point> {p0, p1, x, y}, green))
                return true;
    return false;
}

void removeBetween(Polygon& a) {
    if (SZ(a) < 2) return ;

    sort(ALL(a));
    a[1] = a.back();
    a.resize(2);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;

    int nRed; cin >> nRed;
    Polygon red(nRed);
    REP(i,nRed) cin >> red[i];

    int nGreen; cin >> nGreen;
    Polygon green(nGreen);
    REP(i,nGreen) cin >> green[i];

    Polygon hull = red;
    ConvexHull(hull);

    if (SZ(hull) < 3) cout << 0 << endl;
    else if (SZ(hull) == 3) {
        bool hasInside = false;
        vector<Point> on01, on12, on20;

        for (auto P : red) {
            if (in_convex(hull, P) == INSIDE) {
                hasInside = true;
            }

            if (in_segment(P, hull[0], hull[1])) on01.push_back(P);
            if (in_segment(P, hull[1], hull[2])) on12.push_back(P);
            if (in_segment(P, hull[2], hull[0])) on20.push_back(P);
        }

        if (hasInside) cout << count_in_hull(green, hull) << endl;
        else {
            int cntEmpty = 0;
            if (on01.empty()) ++cntEmpty;
            if (on12.empty()) ++cntEmpty;
            if (on20.empty()) ++cntEmpty;

            removeBetween(on01);
            removeBetween(on12);
            removeBetween(on20);

            if (cntEmpty == 3) cout << 0 << endl;
            else if (cntEmpty == 2) cout << 0 << endl;
            else if (cntEmpty == 0) cout << count_in_hull(green, hull) << endl;
            else {
                int res = 0;
                for (auto P : green) {
                    bool ok = false;

                    if (can(P, hull[0], hull[1], on12, on20)) ok = true;
                    if (can(P, hull[1], hull[2], on20, on01)) ok = true;
                    if (can(P, hull[2], hull[0], on01, on12)) ok = true;

                    if (ok) ++res;
                }
                cout << res << endl;
            }
        }
    } else {
        cout << count_in_hull(green, hull) << endl;
    }
    return 0;
}
