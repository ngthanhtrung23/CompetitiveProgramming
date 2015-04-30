
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

const long long MOD = 1e9 + 7;

long long power(long long x, long long k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;

    long long mid = power(x*x % MOD, k >> 1);
    if (k & 1) return mid * x % MOD;
    else return mid;
}

long long f[111][111*111];
long long c[111][111], pc[2][111][111];

void init() {
    FOR(i,0,100) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int n, k;
    long long m;
    init();
    while (cin >> n >> m >> k) {
        long long times = m / n;
        REP(turn,2) {
            FOR(i,0,100) FOR(j,0,i) {
                pc[turn][i][j] = power(c[i][j], times + turn);
            }
        }
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        FOR(i,0,n-1) FOR(cur,0,k) if (f[i][cur]) {
            int t = (i+1 <= m % n) ? 1 : 0;

            FOR(add,0,n) if (cur + add <= k) {
                f[i+1][cur + add] = (f[i+1][cur + add] + f[i][cur] * pc[t][n][add]) % MOD;
            }
        }
        cout << f[n][k] << endl;
    }
    return 0;
}
