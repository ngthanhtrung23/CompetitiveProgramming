
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

long double f[2][411][211], p[211];
int n, a[211], l, k;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> l >> k) {
        FOR(i,1,n) {
            int t; cin >> t;
            p[i] = t;
        }
        FOR(i,1,n) cin >> a[i];

        memset(f, 0, sizeof f);
        f[0][200 + k][0] = 1.0;
        FOR(i,0,n-1) {
            int t = i % 2;
            memset(f[1-t], 0, sizeof f[1-t]);

            FOR(cap,0,400) FOR(won,0,i)
                if (f[t][cap][won] >= 1e-100) {
                    f[1-t][min(400, cap + a[i+1])][won+1] += f[t][cap][won] / 100.0 * p[i+1];
                    f[1-t][cap][won] += f[t][cap][won] / 100.0 * (100 - p[i+1]);
                }
        }

        long double res = 0.0;
        FOR(cap,200,400) FOR(won,l,n)
            res += f[n%2][cap][won];

        cout << (fixed) << setprecision(10) << res << endl;
    }
    return 0;
}
