
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 200111;
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

int gt[MN], inv_gt[MN];

int get(int dx, int dy) {
    return gt[dx + dy] * inv_gt[dx] % MOD * inv_gt[dy] % MOD;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    gt[0] = 1;
    FOR(i,1,MN-1) gt[i] = gt[i-1] * i % MOD;
    REP(i,MN) {
        inv_gt[i] = power(gt[i], MOD - 2);
        assert(gt[i] * inv_gt[i] % MOD == 1);
    }
    int ntest; cin >> ntest;
    while (ntest--) {
        int m, n, x, y;
        cin >> m >> n >> x >> y;

        int res = get(m-1, n-1);
        res = (res - get(x-1, y-1) * get(m-x, n-y) % MOD) % MOD;
        if (res < 0) res += MOD;
        cout << res << endl;
    }
}
