
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

const ll MOD = 1e9 + 7;
ll f[1011][1011];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n, m, k;
    while (cin >> n >> m >> k) {
        memset(f, 0, sizeof f);
        FOR(layer,0,k) {
            FOR(i,1,1000) {
                if (layer == 0) f[layer][i] = 1;
                else {
                    for(int j = i-2, mult=1; j >= (layer<<1)-1; --j, ++mult)
                        f[layer][i] = (f[layer][i] + f[layer-1][j] * mult) % MOD;
                }
            }
        }
        cout << f[k][m] * f[k][n] % MOD << endl;
    }
    return 0;
}

