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

#define double long double
const int MN = 200111;

struct Point {
    int id;
    int x, y;
    double f;
} a[MN];

bool operator < (const Point& a, const Point& b) {
    return a.f < b.f;
}

const double PI = acos((double) -1.0);
const double EPS = 1e-9;

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            scanf("%d%d", &a[i].x, &a[i].y);
            a[i].id = i;
            a[i].f = atan2(a[i].y, a[i].x);
        }
        FOR(i,n+1,n+n) {
            a[i] = a[i-n];
            a[i].f += 2*PI;
        }
        sort(a+1, a+n+n+1);
        double res = 1e100;
        int u = -1, v = -1;

        FOR(i,1,n+n-1) {
            double cur = a[i+1].f - a[i].f;

			while (cur < -EPS) cur += 2*PI;
			while (cur > 2*PI + EPS) cur -= 2*PI;

			if (cur > PI + 1e-10) cur = 2*PI - cur;

            if (cur < res) {
                res = cur;
                u = a[i].id;
                v = a[i+1].id;
            }
        }

        cout << u << ' ' << v << endl;
    }
}
