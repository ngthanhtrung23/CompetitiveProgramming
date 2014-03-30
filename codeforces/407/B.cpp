#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 1011;
const long long MOD = 1000000007;

long long f[MN][2], p[MN], g[MN];
int n;

void update(long long &x) {
    x %= MOD;
    if (x < 0) x += MOD;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> p[i];

        f[1][1] = 1; f[1][0] = 2; g[1] = 1;
        FOR(i,2,n) {
            f[i][1] = f[i-1][0] + 1;
            if (p[i] != i) {
                f[i][0] = f[i][1] + f[i-1][0] + (g[p[i]] - f[p[i]][0]) + 2;
                g[i] = f[i-1][0] + g[p[i]] - f[p[i]][0] + 2;
            }
            else {
                f[i][0] = f[i][1] + 1;
                g[i] = 1;
            }

            update(f[i][1]);
            update(f[i][0]);
            update(g[i]);

            // cout << f[i][1] << ' ' << f[i][0] << ' ' << g[i] << endl;
        }
        cout << f[n][0] << endl;
    }
    return 0;
}
