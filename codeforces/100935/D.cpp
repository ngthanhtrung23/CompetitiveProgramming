
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

int power(int x, int k, int MOD) {
    int res = 1;
    while (k > 0) {
        if (k & 1) res = res * x % MOD;
        x = x * x % MOD;
        k >>= 1;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int test = 0;
    int n, k, a;
    while (cin >> n >> k >> a && n) {
        int q; cin >> q;
        cout << "Case " << ++test << ":\n";
        FOR(i,1,q) {
            int MOD; cin >> MOD;
            
            int res = a * power(k, n, MOD) % MOD;
            cout << res;
            if (i < q) cout << ' '; else cout << '\n';
        }
    }
}
