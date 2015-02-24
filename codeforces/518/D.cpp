
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

const int MN = 2011;

double f[MN][MN];
int n, t;
double p;

int main() {
    while (cin >> n >> p >> t) {
        memset(f, 0, sizeof f);
        f[0][n] = 1.0;
        FOR(i,0,t-1) FOR(j,0,n) if (f[i][j] > 1e-100) {
            if (j == 0) f[i+1][j] += f[i][j];
            else {
                f[i+1][j] += f[i][j] * (1 - p);
                f[i+1][j-1] += f[i][j] * p;
            }
        }
        double res = 0.0;
        FOR(j,0,n) res += f[t][j] * (n - j);
        cout << (fixed) << setprecision(12) << res << endl;
    }
    return 0;
}
