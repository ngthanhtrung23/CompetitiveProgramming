#include <bits/stdc++.h>
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
    return sqrt(max(0.0,x));
}

const int MN = 311;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    
    Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
    int operator % (const Point& a) const { return x*a.y - y*a.x; }
} a[MN];
int n;
int f[MN][MN];

int ccw(Point a, Point b, Point c) {
    int t = (b - a) % (c - a);
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}

bool inTriangle(Point a, Point b, Point c, Point p) {
    return ccw(a, b, c) == ccw(a, b, p)
        && ccw(b, c, a) == ccw(b, c, p)
        && ccw(c, a, b) == ccw(c, a, p);
}
Point O(0, 0);

bool check(int i, int j, int k) {
    Point A = a[i], B = a[j], C = a[k];

    if (ccw(B, C, O) == 0) return f[i][j] - f[i][k] == 0;
    if (ccw(A, C, O) == 0) return f[i][j] - f[j][k] == 0;

    if (inTriangle(A, B, O, C)) {
        return f[i][j] - f[j][k] - f[k][i] == 1;
    }
    else {
        if (ccw(O, B, A) == ccw(O, B, C)) return f[i][j] + f[i][k] - f[j][k] == 0;
        else return f[i][j] + f[j][k] - f[i][k] == 0;
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("farmer.in", "r", stdin);
    freopen("farmer.out", "w", stdout);

    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].x >> a[i].y;
            a[i].x += 10111;
            a[i].y += 77766;
        }
        FOR(i,1,n) FOR(j,i+1,n) {
            int cnt = 0;
            FOR(k,1,n) if (inTriangle(O, a[i], a[j], a[k])) ++cnt;

            f[i][j] = f[j][i] = cnt;
        }

        int res = 0;
        FOR(i,1,n) FOR(j,i+1,n) FOR(k,j+1,n) {
            int cur = 0;
            if (ccw(a[i], a[j], a[k]) == ccw(a[i], a[j], O)) cur += check(i, j, k);
            else if (ccw(a[j], a[k], a[i]) == ccw(a[j], a[k], O)) cur += check(j, k, i);
            else if (ccw(a[k], a[i], a[j]) == ccw(a[k], a[i], O)) cur += check(k, i, j);

            res += cur;
        }
        cout << res << endl;
    }
}
