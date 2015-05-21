
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int main() {
    ios :: sync_with_stdio(false);
    int n, a, d;
    while (cin >> n >> a >> d) {
        double last = 0.0;
        FOR(i,1,n) {
            int t0, v;
            cin >> t0 >> v;
            double t1 = v / (double) a;
            double d1 = a * t1 * t1 / 2.0;
            
            double t = 0.0;
            if (d1 >= d) t = sqrt(2*d / (double) a);
            else {
                t = t1 + (d - d1) / (double) v;
            }
            t += t0;

            if (t < last) t = last;
            last = t;
            printf("%.9lf\n", t);
        }
    }
    return 0;
}
