
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

double b1, t1, b2, t2, l, ds, df, g, vxvy, vxvy2;

double get_vmax_vy_D(double vy2, double D) {
    return vy2 + vxvy2 / vy2;
}

double get_vmax(double ds, double low, double high, double D) {
    double t1 = ds / D;
    double t3 = 2.0 / g * (t1 - sqr(t1));

    vxvy = 0.5 * g * D;
    vxvy2 = vxvy * vxvy;

    double L = low / t3;
    double R = high / t3;

    double vmax = get_vmax_vy_D(L, D);
    vmax = min(vmax, get_vmax_vy_D(R, D));

    double vy2 = vxvy;
    if (L < vy2 && vy2 < R) vmax = min(vmax, get_vmax_vy_D(vy2, D));
    return vmax;
}

double get_vmax(double D) {
    return max(get_vmax(ds, b1, t1, D), get_vmax(df, b2, t2, l + df - (D - ds)));
}

double ternary(double l, double r) {
    double res = 1e100;
    REP(turn,30) {
        double x1 = (l + l + r) / 3.0;
        double x2 = (l + r + r) / 3.0;
        double y1 = get_vmax(x1);
        double y2 = get_vmax(y2);

        res = min(res, min(y1, y2));

        if (y1 < y2) r = x2;
        else l = x1;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("jumper.in", "r", stdin);
    freopen("jumper.out", "w", stdout);
    while (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &b1, &t1, &b2, &t2, &l, &ds, &df, &g) == 8) {
        double L = ds, R = ds + l;
        double res = 1e100;
        REP(outer,20) {
            double best = 1e100;
            double worst = -1e100;
            double savemid;
            int K = 100;
            double range = (R - L) / K;

            REP(turn,K) {
                double l = L + range * turn;
                double r = l + range;
                double mid = (l + r) / 2.0;

                double cur = get_vmax(mid);
                worst = max(worst, cur);
                if (cur < best) {
                    best = cur;
                    savemid = mid;
                }

                l += range;
                r += range;
            }
            if (fabs(best - worst) < 1e-6) break;
            range *= 10;
            L = savemid - range;
            R = savemid + range;
            if (L < ds) L = ds;
            if (R > ds + l) R = ds + l;

            res = min(res, best);
        }
        res = sqrt(res);
        printf("%.6f\n", res);
    }
}
