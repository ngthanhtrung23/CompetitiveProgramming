
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

int T;
double c, d;
double x[10111], sum[10111];

double f(int t, double eps) {
    double v = d / (t + eps) * 60;
    double res = 1e100;

    FOR(i,1,T-t) {
        double cur;
        cur = sum[i+t-1] - sum[i-1];
        cur += eps * x[i+t];
        res = min(res, cur);

        cur = sum[i+t] - sum[i];
        cur += eps * x[i];
        res = min(res, cur);
    }
    return res + c * v * v * (t + eps);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> T) {
        cin >> c >> d;
        FOR(i,1,T) {
            cin >> x[i];
            sum[i] = sum[i-1] + x[i];
        }
        double res = 1e100;
        FOR(t,0,T-1) {
            double l = 0.0, r = 1.0;
            if (t == 0) l = 1e-9;
            REP(turn,50) {
                double x1 = (l + l + r) / 3.0;
                double x2 = (l + r + r) / 3.0;
                if (f(t, x1) < f(t, x2)) r = x2;
                else l = x1;
            }
            res = min(res, f(t, (l + r) / 2.0));
        }
        cout << (fixed) << setprecision(9) << res << endl;
    }
}
