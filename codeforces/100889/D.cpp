
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

const int MN = 2000111;
const int MOD = 1e9 + 7;

int sieve[MN];

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

void init() {
    FOR(i,2,2000) if (!sieve[i]) {
        for(int j = i*i; j < MN; j += i) {
            sieve[j] = i;
        }
    }
}

int C(int n, int k) {
    k = min(k, n-k);
    int res = 1;
    FOR(i,n-k+1,n) res = res * i % MOD;
    FOR(i,1,k) res = res * inverse(i) % MOD;
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    init();
    int ntest; GI(ntest);
    while (ntest--) {
        int n, m;
        GI(n); GI(m);
        int res = 1;
        while (n > 1) {
            int p = (sieve[n] ? sieve[n] : n);
            int k = 0;
            while (n % p == 0) {
                n /= p;
                ++k;
            }
            res = res * C(k+m-1, m-1) % MOD;
        }
        printf("%lld\n", res);
    }
}
