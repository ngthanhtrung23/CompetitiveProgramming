#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

inline int cmp(long long a, long long b) {
    if (a == b) return 0;
    else if (a < b) return -1;
    else return 1;
}

struct Point {
    long long x, y;
    Point(long long x = 0.0, long long y = 0.0) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }

    long long operator * (Point a) { return x*a.x + y*a.y; } // dot product
    long long operator % (Point a) { return x*a.y - y*a.x; } // cross product

    int cmp(Point q) const { if (int t = ::cmp(x,q.x)) return t; return ::cmp(y,q.y); }

    #define Comp(x) bool operator x (Point q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
    #undef Comp

    Point conj() { return Point(x, -y); }
    long long norm() { return x*x + y*y; }

    Point rotate(long long alpha) {
        long long cosa = cos(alpha), sina = sin(alpha);
        return Point(x * cosa - y * sina, x * sina + y * cosa);
    }
};

int ccw(Point a, Point b, Point c) {
    return cmp((b-a)%(c-a),0);
}

typedef vector< Point > Polygon;

// Convex Hull: returns minimum number of vertices. Should work when N <= 1 and when all points 
// are collinear
struct comp_hull {
    Point pivot;
    bool operator() (Point q,Point w) {
        Point Q = q - pivot, W = w - pivot;
        long long R = Q % W;
        if (cmp(R,0)) return R < 0;
        return cmp(Q*Q,W*W) < 0;
    }
};
Polygon convex_hull(Polygon p) { // minimum vertices
    int j = 0, k, n = p.size();
    Polygon r(n);
    if (!n) return r;
    comp_hull comp;
    comp.pivot = *min_element(p.begin(),p.end());
    sort(p.begin(),p.end(),comp);
    for(int i = 0; i < n; ++i) {
        while (j > 1 && ccw(r[j-1],r[j-2],p[i]) <= 0) j--;
        r[j++] = p[i];
    }
    r.resize(j);
    if (r.size() >= 2 && r.back() == r.front()) r.pop_back();
    return r;
}

long long area(Point a, Point b, Point c) {
    return llabs((b-a) % (c-a));
}

int n;
long long f1[1011][1011], f2[1011][1011];

#define next(k) ((k-1+a.size())%a.size())

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        Polygon a;
        FOR(i,1,n) {
            Point p; cin >> p.x >> p.y;
            a.push_back(p);
        }
        a = convex_hull(a);
        // REP(i,a.size()) {
            // cout << a[i].x << ' ' << a[i].y << endl;
        // }
        long long res = 0;
        REP(i,a.size()) {
            long long k = i;
            FOR(j,i,a.size()-1) {
                while (k < j && area(a[i], a[k+1], a[j]) > area(a[i], a[k], a[j])) ++k;
                f1[i][j] = area(a[i], a[k], a[j]);
            }

            k = i;
            int j = a.size()-1;
            while (k < j && area(a[i], a[next(k)], a[j]) > area(a[i], a[k], a[j])) k = next(k);
            FORD(j,a.size()-1,i) {
                while (next(k) != j && area(a[i], a[next(k)], a[j]) > area(a[i], a[k], a[j])) k = next(k);
                f2[i][j] = area(a[i], a[k], a[j]);
            }

            FOR(j,i,a.size()-1) {
                res = max(res, f1[i][j] + f2[i][j]);
            }
        }
        if (res % 2) cout << res / 2 << ".5\n";
        else cout << res / 2 << "\n";
    }
    return 0;
}
