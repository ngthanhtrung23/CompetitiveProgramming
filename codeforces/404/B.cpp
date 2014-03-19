#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

double a, d;
int n;

int main() {
    double zero = 0;
    while (scanf("%lf%lf%d", &a, &d, &n) == 3) {
        double pos = 0.0;
        while (d > 4*a) d -= 4*a;

        FOR(i,1,n) {
            if (a < 1e-6) {
                printf("%.6lf %.6lf\n", zero, zero);
                continue;
            }
            pos += d;
            while (pos >= 4*a) pos -= 4*a;

            if (pos <= a) {
                printf("%.6lf %.6lf\n", pos, zero);
            }
            else if (pos <= a+a) {
                printf("%.6lf %.6lf\n", a, pos-a);
            }
            else if (pos <= a+a+a) {
                printf("%.6lf %.6lf\n", (3*a-pos), a);
            }
            else {
                printf("%.6lf %.6lf\n", zero, (4*a-pos));
            }
        }
    }
    return 0;
}
