
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

int n;
double g;
double d[11], theta[11];
double PI = acos(-1.0);

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> g) {
        FOR(i,1,n) {
            cin >> d[i] >> theta[i];
            theta[i] = theta[i] / 90.0 * (PI / 2);
        }
        FOR(i,1,n) {
            double v0 = 0.0;
            FOR(j,i,n) {
                double a = g * cos(theta[j]);
                double delta = v0*v0 + 2*a*d[j];
                double t = (-v0 + sqrt(delta)) / a;

                v0 += a * t;
            }
            cout << (fixed) << setprecision(9) << v0 << endl;
        }
    }
}
