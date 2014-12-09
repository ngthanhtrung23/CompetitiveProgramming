#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 211;
struct Point {
    long long x, y;

    Point(long long x = 0, long long y = 0) : x(x), y(y) {}

    Point operator + (Point a) { return Point(x+a.x, y+a.y); }
    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
    Point operator * (long long k) { return Point(x*k, y*k); }
    Point operator / (long long k) { return Point(x/k, y/k); }

    long long operator * (Point a) { return x*a.x + y*a.y; } // dot product
    long long norm() { return x*x + y*y; }
    bool operator == (Point a) { return x == a.x && y == a.y; }
} a[MN];
int n;

int ccw(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    long long t = b.x * c.y - b.y * c.x;
    if (t == 0) return 0;
    else if (t < 0) return -1;
    else return 1;
}

const long long MOD = 1000000007;
long long f[211][211];
bool good[211][211];

bool intersect(Point a, Point b, Point c, Point d) {
    return ccw(a, b, c) * ccw(a, b, d) < 0
            && ccw(c, d, a) * ccw(c, d, b) < 0;
}

int next(int u) {
    if (u == n) return 1;
    else return u + 1;
}

bool between(Point a, Point b, Point c) {
    if (a == c) return false;
    if (b == c) return false;
    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x)
            && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}

#define EPS 1e-6
double angle(Point a, Point o, Point b) { // angle AOB
    a = a - o; b = b - o;
    return acos((a * b) / sqrt(a.norm() * (double) b.norm()));
}
bool in_polygon(Point pt) {
    FOR(i,1,n) {
        if (pt == a[i]) return true;
        Point Pj = a[next(i)];
        if (ccw(a[i], Pj, pt) == 0 && between(a[i], Pj, pt)) return true;
    }
    double sum = 0;
    FOR(i,1,n) {
        Point Pj = a[next(i)];
        if (ccw(pt, a[i], Pj) > 0)
            sum += angle(a[i], pt, Pj);
        else sum -= angle(a[i], pt, Pj);
    }
    return fabs(fabs(sum) - 2*acos(-1)) < 1e-3;
}

bool check(int i, int j) {
    FOR(x,1,n) {
        if (ccw(a[i], a[j], a[x]) == 0 && between(a[i], a[j], a[x])) return false;
        if (intersect(a[i], a[j], a[x], a[next(x)])) return false;
    }
    Point mid = (a[i] + a[j]) / 2;
    return in_polygon(mid);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].x >> a[i].y;
            a[i] = a[i] * 2;
        }
        memset(f, 0, sizeof f);
        FOR(i,1,n) FOR(j,i+1,n)
            good[i][j] = good[j][i] = check(i, j);

        FORD(i,n,1) FOR(j,i+1,n) {
            if (j == i + 1) {
                f[i][j] = 1;
                continue;
            }
            if (!good[i][j]) continue;

            if (j == i + 2) f[i][j] = 1;
            else {
                FOR(k,i+1,j-1)
                    if (good[i][k] && good[k][j])
                        f[i][j] = (f[i][j] + f[i][k] * f[k][j]) % MOD;
            }
        }
        cout << f[1][n] << endl;
    }
    return 0;
}

