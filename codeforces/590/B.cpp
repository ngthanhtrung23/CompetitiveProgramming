
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

struct Point {
    double x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    Point operator - (const Point& a) const {
        return Point(x-a.x, y-a.y);
    }
    Point operator + (const Point& a) const {
        return Point(x+a.x, y+a.y);
    }
    Point operator * (double k) const {
        return Point(x*k, y*k);
    }

    double len() {
        return sqrt(x*x + y*y);
    }

    bool read() {
        if (!(cin >> x >> y)) return false;
        return true;
    }
} start, target, wind1, wind2;

double vmax, t;

bool check1(double k) {
    Point dist = target - start;
    dist = dist - wind1 * k;

    double vneed = dist.len() / k;
    return vneed <= vmax;
}

double solve1() {
    double l = 1e-9, r = t;
    double res = t * 10;
    REP(turn,10000) {
        double mid = (l + r) / 2.0;
        if (check1(mid)) {
            res = mid;
            r = mid;
        }
        else l = mid;
    }
    return res;
}

bool check2(double k) {
    Point dist = target - start;
    dist = dist - wind1 * t;
    dist = dist - wind2 * (k - t);

    double vneed = dist.len() / k;
    return vneed <= vmax;
}

double solve2() {
    double l = t, r = 1e50;
    double res = r;

    REP(turn,10000) {
        double mid = (l + r) / 2.0;
        if (check2(mid)) {
            res = mid;
            r = mid;
        }
        else l = mid;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    int x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        start = Point(x1, y1);
        target = Point(x2, y2);
        cin >> vmax >> t;
        wind1.read();
        wind2.read();

        if (x1 == x2 && y1 == y2) {
            cout << 0 << endl;
            continue;
        }

        double res = solve1();
        if (res > t) res = solve2();

        cout << (fixed) << setprecision(12) << res << endl;
    }
}

