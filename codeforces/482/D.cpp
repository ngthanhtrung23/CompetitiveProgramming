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

const int MN = 100111;
const long long MOD = 1000000007;

vector<int> ke[MN];
long long f[2][MN];

void dfs(int u) {
    f[0][u] = 0;
    f[1][u] = 1;
    for(int v : ke[u]) {
        dfs(v);

        long long f0 = (f[0][u] * (f[0][v] + 1) + f[1][u] * f[1][v]) % MOD;
        long long f1 = (f[0][u] * f[1][v] + f[1][u] * (f[0][v] + 1)) % MOD;

        f[0][u] = f0;
        f[1][u] = f1;
    }
    f[0][u] = (2 * f[0][u]) % MOD;
    f[1][u] = (2 * f[1][u]) % MOD;

    long long t[2];
    // Odd child, each: odd --> subtract from f[0][u]
    t[0] = 1; t[1] = 0;
    for(int v : ke[u]) {
        long long t0 = (t[0] + t[1] * f[1][v]) % MOD;
        long long t1 = (t[1] + t[0] * f[1][v]) % MOD;

        t[0] = t0;
        t[1] = t1;
    }
    f[0][u] = (f[0][u] - t[1] + MOD) % MOD;

    // Even child, each: even --> subtract from f[1][u]
    // Odd child, each: even --> subtract from f[1][u]
    t[0] = 1; t[1] = 0;
    for(int v : ke[u]) {
        long long t0 = (t[0] + t[1] * f[0][v]) % MOD;
        long long t1 = (t[1] + t[0] * f[0][v]) % MOD;

        t[0] = t0;
        t[1] = t1;
    }
    f[1][u] = (f[1][u] - t[0] - t[1] + MOD + MOD) % MOD;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int fi; cin >> fi;
            ke[fi].push_back(i);
        }
        dfs(1);
//        PR(f[0], n);
//        PR(f[1], n);

        cout << (f[0][1] + f[1][1]) % MOD << endl;
    }
    return 0;
}
