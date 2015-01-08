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

int n, q;
long long a, b, f[MN];
long long x[MN], add[MN], tmp[MN];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> q) {
        cin >> f[1] >> f[2];
        cin >> a >> b;
        FOR(i,3,MN-1) f[i] = (f[i-2] * a + f[i-1] * b) % MOD;
        
        memset(x, 0, sizeof x);
        memset(add, 0, sizeof add);
        FOR(i,1,n) cin >> x[i];

        while (q--) {
            int l, r; cin >> l >> r;
            if (l == r) {
                x[l] = (x[l] + f[1]) % MOD;
                continue;
            }
            add[l] = (add[l] + f[1]) % MOD;
            add[l+1] = (add[l+1] + f[2] - b * f[1] % MOD + MOD) % MOD;
            add[r+1] = (add[r+1] - f[r - l + 2] + MOD) % MOD;
            add[r+2] = (add[r+2] - a * f[r - l + 1] % MOD + MOD) % MOD;

//            cout << l << ' ' << r << endl;
//            PR(add, n);
        }
        FOR(i,2,n) add[i] = (add[i] + b * add[i-1] + a * add[i-2]) % MOD;
        FOR(i,1,n) x[i] = (x[i] + add[i]) % MOD;

        FOR(i,1,n) cout << x[i] << ' '; cout << endl;
    }
    return 0;
}

