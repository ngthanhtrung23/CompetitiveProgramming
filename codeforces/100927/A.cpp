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
int GI(ll& x) {
    return scanf("%lld", &x);
}

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    Point operator + (const Point& a) const { return Point(x+a.x, y+a.y); }

    int operator % (const Point& a) const { return x*a.y - y*a.x; }
    int sqlen() const { return x*x + y*y; }
} a[55];

int ccw(Point a, Point b, Point c) {
    int t = (b - a) % (c - a);
    if (t == 0) return 0;
    else if (t < 0) return -1;
    return 1;
}
const int RE_TRAI = ccw(Point(0, 0), Point(0, 1), Point(-1, 1));
const int RE_PHAI = ccw(Point(0, 0), Point(0, 1), Point(+1, 1));
int n;

Point O;
Point cur[55];
int f[55][55];
int k;

bool operator < (const Point& a, const Point& b) {
    int t = ccw(O, a, b);
    if (t == RE_TRAI) return true;
    if (t == RE_PHAI) return false;

    return (a - O).sqlen() < (b - O).sqlen();
}

bool order(Point a, Point b, Point c) {
    return min(a.x, c.x) <= b.x && b.x <= max(a.x, c.x)
        && min(a.y, c.y) <= b.y && b.y <= max(a.y, c.y);
}

int solve() {
    bool good = 0;
    FOR(i,2,k) if (ccw(O, cur[i], cur[i+1])) good = 1;
    if (good == 0) return k;

    int res = 0;
    FOR(i,1,k) FOR(j,i+1,k) {
        f[i][j] = max(f[i][j], 2LL);

        if (ccw(cur[i], cur[j], O)) {
            int add = 0;
            FOR(u,1,k) {
                if (u != i && u != j && ccw(cur[j], cur[u], O) == 0 && order(cur[j], cur[u], O))
                    ++add;
            }
            res = max(res, f[i][j] + add);
        }

        FOR(u,j+1,k) {
            if (ccw(cur[i], cur[j], cur[u]) != RE_PHAI) {
                f[j][u] = max(f[j][u], f[i][j] + 1);
            }
        }
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("convex.in", "r", stdin);
    freopen("convex.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i].x >> a[i].y;

        FOR(i,1,n) FOR(j,i+1,n)
            assert(a[i].x != a[j].x || a[i].y != a[j].y);

        int res = 0;
        FOR(i,1,n) {
            O = a[i];
            k = 0;
            FOR(j,1,n) if (a[j].y > a[i].y || (a[j].y == a[i].y && a[j].x > a[i].x)) {
                cur[++k] = a[j];
            }

            sort(cur+1, cur+k+1);
            memset(f, 0, sizeof f);

            res = max(res, 1 + solve());
        }
        cout << res << endl;
    }
}
