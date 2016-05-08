
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

const int MOD = 1e9 + 7;
int c[1011][1011];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;

    FOR(i,0,1000) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
    }
    while (ntest--) {
        int n, m, k, d;
        cin >> n >> m >> k >> d;
        if (k > m) k = m;
        int good = 0;
        FOR(i,1,n) {
            int a; cin >> a;
            if (a >= d) ++good;
        }
        ll res = 0;
        FOR(i,k,good) {
            if (n >= good && m >= i)
            res = (res + c[good][i] * c[n-good][m-i]) % MOD;
        }
        cout << res << endl;
    }
}
