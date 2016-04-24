
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

const int MOD = 1e9 + 9;
int f[311][311];
int n, k;

void update(int& f, int x) {
    f += x;
    if (f >= MOD) f -= MOD;
}

int solve(int k) {
    if (k < 0) return 0;

    memset(f, 0, sizeof f);
    f[0][0] = 1;
    FOR(i,0,299) FOR(sum,0,300) if (f[i][sum]) {
        // add 0
        update(f[i+1][sum], f[i][sum]);
        // add (
        if (sum < k) update(f[i+1][sum+1], f[i][sum]);
        // add )
        if (sum) update(f[i+1][sum-1], f[i][sum]);
    }
    return f[n][0];
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> k) {
        cout << (solve(k) - solve(k-1) + MOD) % MOD << endl;
    }
}
