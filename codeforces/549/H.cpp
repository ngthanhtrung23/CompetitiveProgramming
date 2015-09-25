
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
double a, b, c, d;

double getMin(double a, double d, double x) {
    double w = (a - x) * (d - x);
    double y = (a - x) * (d + x);
    double z = (a + x) * (d - x);
    double t = (a + x) * (d + x);

    return min(min(w, y), min(z, t));
}
double getMax(double a, double d, double x) {
    double w = (a - x) * (d - x);
    double y = (a - x) * (d + x);
    double z = (a + x) * (d - x);
    double t = (a + x) * (d + x);

    return max(max(w, y), max(z, t));
}

bool check(double x) {
    double min1 = getMin(a, d, x);
    double max1 = getMax(a, d, x);

    double min2 = getMin(b, c, x);
    double max2 = getMax(b, c, x);

    if (max1 < min2 || max2 < min1) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(12);
    while (cin >> a >> b >> c >> d) {
        double l = 0, r = 1e9, res = 1e9;
        REP(turn,500) {
            double x = (l + r) / 2.0;
            if (check(x)) res = r = x;
            else l = x;
        }
        cout << res << endl;
    }
}
