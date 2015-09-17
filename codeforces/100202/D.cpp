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
using namespace std;

double res, p1, p2, q1, q2;

double update(double a, double b, double c, double d) {
    double cur = a + b + c + d;
    if (cur < res) {
        res = cur;

        p1 = 1;
        q1 = a;
        q2 = b;

        p2 = c / q1;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("lab.in", "r", stdin);
    freopen("lab.out", "w", stdout);

    ll a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        res = 1e20;
        if (a*d >= b*c) {
            update(a, b, a * d / (double) b, d);
            update(a, a * d / (double) c, c, d);

            if (b*b <= a*d && c*c <= a*d) {
                update(a, sqrt(a*(double)d), sqrt(a*(double)d), d);
            }
        }
        else {
            update(a, b, c, b * c / (double) a);
            update(b * c / (double) d, b, c, d);

            if (a*a <= b*c && d*d <= b*c) {
                update(sqrt(b*(double)c), b, c, sqrt(b*(double)c));
            }
        }
        cout << (fixed) << setprecision(9);
        cout << res << endl;
        cout << p1 << ' ' << p2 << ' ' << q1 << ' ' << q2 << endl;
    }
}