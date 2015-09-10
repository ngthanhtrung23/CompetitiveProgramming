
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
#define double long double
using namespace std;

struct Point {
    double x, y, z;

    Point() {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    Point operator - (const Point& a) const {
        return Point(x-a.x, y-a.y, z-a.z);
    }

    Point operator + (const Point& a) const {
        return Point(x+a.x, y+a.y, z+a.z);
    }

    Point operator / (double k) const {
        return Point(x/k, y/k, z/k);
    }

    Point operator * (double k) const {
        return Point(x*k, y*k, z*k);
    }

    double len() {
        return sqrt(x*x + y*y + z*z);
    }

    void read() {
        cin >> x >> y >> z;
    }
} P[10111], H, cur;
double vp, vh, t[10111];
int n;

bool can(double time) {
    int i = 0;
    while (i < n && t[i+1] <= time) {
        ++i;
    }
    double extra = time - t[i];
    if (extra < 1e-12) {
        cur = P[i];
    } else {
        cur = P[i] + (P[i+1] - P[i]) / (P[i+1] - P[i]).len() * extra * vp;
    }

    return (H - cur).len() / vh <= time + 1e-12;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(12);
    while (cin >> n) {
        FOR(i,0,n) P[i].read();
        cin >> vh >> vp;
        H.read();

        t[0] = 0;
        FOR(i,1,n) {
            t[i] = t[i-1] + (P[i] - P[i-1]).len() / vp;
        }

        if (!can(t[n])) {
            puts("NO");
            continue;
        }
        double l = 0., r = t[n], res = t[n];
        REP(turn,500) {
            double mid = (l + r) / 2.0;
            if (can(mid)) {
                res = mid;
                r = mid;
            }
            else l = mid;
        }
        cout << "YES\n";
        cout << res << '\n';
        cout << cur.x << ' ' << cur.y << ' ' << cur.z << '\n';
    }
}

