
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }
const int MOD = 1e9 + 7;

int f[1000111][22];
int sieve[1000111];

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);

    // f[t][k] = ft(p^k)
    FOR(i,0,20) if (i == 0) f[0][i] = 1; else f[0][i] = 2;
    FOR(i,1,1000*1000) {
        f[i][0] = 1;
        FOR(j,1,20) {
            f[i][j] = f[i][j-1] + f[i-1][j];
            if (f[i][j] >= MOD) f[i][j] -= MOD;
        }
    }
    FOR(i,2,1000) if (!sieve[i]) {
        for(int j = i*i; j <= 1000000; j += i)
            sieve[j] = i;
    }

    int ntest; GI(ntest);
    while (ntest--) {
        int r, n; GI(r); GI(n);

        int u = n;
        int res = 1;
        while (u > 1) {
            int p = sieve[u] ? sieve[u] : u;
            int k = 0;
            while (u % p == 0) {
                u /= p;
                k++;
            }
            // fr(n) is multiplicative function
            // --> fr(n) = product(fr(p^k))
            res = res * f[r][k] % MOD;
        }
        printf("%lld\n", res);
    }
}
