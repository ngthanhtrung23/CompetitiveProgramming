
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

struct Point {
    int x, y;
    Point() { x = y = 0; }
    Point(int x, int y) : x(x), y(y) {}

    Point operator - (const Point& a) const {
        return Point(x-a.x, y-a.y);
    }
    int operator % (Point a) { return x*a.y - y*a.x; } // cross product
};
int ccw(Point a, Point b, Point c) {
    int t = (b - a) % (c - a);
    if (t == 0) return 0;
    if (t < 0)  return -1;
    return 1;
}
int signed_area(vector<Point> p) {
    int area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (scanf("%lld", &n) == 1) {
        vector<Point> p; p.resize(n);
        REP(i,n+1) {
            int x, y; scanf("%lld%lld", &x, &y);
            if (i != n) p[i] = Point(x, y);
        }
        int s = signed_area(p);

        int cnt = 0;
        REP(i,n) {
            int j = (i + 1) % n;
            int k = (i + 2) % n;

            if (ccw(p[i], p[j], p[k]) * s < 0) ++cnt;
        }
        cout << cnt << endl;
    }
}
