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

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 200111;
const int MOD = 1e9 + 7;
int gt[MN], cat[MN];

int power(int x, int k) {
    int res = 1;
    while (k > 0) {
        if (k & 1) res = res * x % MOD;

        k >>= 1;
        x = x * x % MOD;
    }
    return res;
}

int inv(int x) {
    return power(x, MOD - 2);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);

    gt[0] = 1; FOR(i,1,MN-1) gt[i] = gt[i-1] * i % MOD;

    int n;
    while (GI(n) == 1) {
        int x = 0, y = 0, z = 0;
        FOR(i,1,n) {
            int a; GI(a);
            if (a == 1) ++x;
            if (a == 2) ++y;
            if (a == 3) ++z;
        }

        if (x + 2*y + 3*z != 2*n-2) {
            cout << 0 << endl;
            continue;
        }

        int res = gt[n-2] * inv(power(2, z)) % MOD;

        cout << res << endl;
    }
}
