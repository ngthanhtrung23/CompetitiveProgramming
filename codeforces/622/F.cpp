
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;
#define int long long

const int MOD = 1e9 + 7;

int power(int x, int k) {
    int res = 1;
    while (k > 0) {
        if (k & 1) res = res * x % MOD;
        x = x * x % MOD;
        k >>= 1;
    }
    return res;
}
int inverse(int x) {
    return power(x, MOD - 2);
}

const int MN = 1000111;
int y[MN], gt[MN], inv_gt[MN], f[MN], l[MN], r[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);

    gt[0] = 1; FOR(i,1,MN-1) gt[i] = gt[i-1] * i % MOD;
    FOR(i,0,MN) inv_gt[i] = inverse(gt[i]);

    int x, k;
    while (cin >> x >> k) {
        int n = k + 2;
        FOR(i,1,n) y[i] = power(i, k);
        FOR(i,1,n) y[i] = (y[i-1] + y[i]) % MOD;
        int res = 0;

        FOR(i,1,n) {
            f[i] = (x - i + MOD) % MOD;
        }
        l[0] = 1; FOR(i,1,n) l[i] = l[i-1] * f[i] % MOD;
        r[n+1] = 1; FORD(i,n,1) r[i] = r[i+1] * f[i] % MOD;

        FOR(i,1,n) {
            int cur = l[i-1] * inv_gt[i - 1] % MOD;

            cur = cur * r[i+1] % MOD * inv_gt[n - i] % MOD;
            if ((n - i) % 2) cur = cur * (MOD - 1) % MOD;

            res = (res + cur * y[i]) % MOD;
        }
        cout << res << endl;
    }
}
