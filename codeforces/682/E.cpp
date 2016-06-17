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
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}

    Point operator + (const Point& a) const {
        return Point(x+a.x, y+a.y);
    }
    Point operator - (const Point& a) const {
        return Point(x-a.x, y-a.y);
    }
    int operator % (const Point& a) const {
        return x*a.y - y*a.x;
    }
    bool operator<(const Point &rhs) const { return make_pair(y,x) < make_pair(rhs.y,rhs.x); }
    bool operator==(const Point &rhs) const { return make_pair(y,x) == make_pair(rhs.y,rhs.x); }
};
int ccw(Point a, Point b, Point c) {
    int t = (b - a) % (c - a);
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}

typedef vector< Point > Polygon;
int area2(Point a, Point b, Point c) { return a%b + b%c + c%a; }
bool between(const Point &a, const Point &b, const Point &c) {
    return (area2(a,b,c) == 0 && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
void ConvexHull(vector<Point> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<Point> up, dn;
    for (int i = 0; i < pts.size(); i++) {
        while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
    
    if (pts.size() <= 2) return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < pts.size(); i++) {
        if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, t;
    while (cin >> n >> t) {
        Polygon a; a.resize(n);
        REP(i,n) cin >> a[i].x >> a[i].y;
        
        ConvexHull(a);
        n = SZ(a);

        int best = -1;
        int savei = -1, savej = -1, savek = -1;
        REP(i,n-2) {
            int k = i+2;
            FOR(j,i+1,n-2) {
                if (k < j+1) k = j+1;
                while (k < n-1 && area2(a[i], a[j], a[k]) <= area2(a[i], a[j], a[k+1])) ++k;

                int cur = area2(a[i], a[j], a[k]);
                if (cur > best) {
                    best = cur;
                    savei = i;
                    savej = j;
                    savek = k;
                }
            }
        }

        Point A = a[savei];
        Point B = a[savej];
        Point C = a[savek];

        Point X = B + (C - A);
        Point Y = C + (A - B);
        Point Z = A + (B - C);

        cout << X.x << ' ' << X.y << endl;
        cout << Y.x << ' ' << Y.y << endl;
        cout << Z.x << ' ' << Z.y << endl;
    }
}
