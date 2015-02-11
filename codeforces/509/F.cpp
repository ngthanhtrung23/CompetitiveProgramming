
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

long long MOD = 1e9 + 7;

// f[i][j] = number of trees from a[i]..a[j]
// g[i][j] = number of forests from a[i]..a[j]
long long f[511][511], g[511][511], a[511];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FORD(i,n,1) FOR(j,i,n) {
            if (i == j) {
                f[i][j] = g[i][j] = 1;
            }
            else {
                // only 1 child
                f[i][j] = f[i+1][j];
                // at least 2 child
                FOR(k,i+1,j-1)
                    if (a[i+1] < a[k+1])
                        f[i][j] = (f[i][j] + f[i+1][k] * g[k+1][j]) % MOD;

                // only 1 tree
                g[i][j] = f[i][j];
                FOR(k,i,j-1)
                    if (a[i] < a[k+1])
                        g[i][j] = (g[i][j] + f[i][k] * g[k+1][j]) % MOD;
            }
//            cout << i << ' ' << j << ":   "; FOR(x,i,j) cout << a[x] << ' '; cout << endl;
//            cout << f[i][j] << ' ' << g[i][j] << endl;
        }
        cout << f[1][n] << endl;
    }
    return 0;
}

