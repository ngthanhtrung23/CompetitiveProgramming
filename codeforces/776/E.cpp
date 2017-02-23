
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
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define PI (2 * acos((double)0))
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define y0 u9cqu3jioajc

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 1000111;
int sieve[MN];
pair<int,int> pk[MN];
int f[MN], g[MN];

int getF(int n) {
    if (n < MN) {
        return f[n];
    }

    int res = 1;
    for(int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            int u = 1;
            while (n % i == 0) {
                n /= i;
                u *= i;
            }
            res *= u / i * (i-1);
        }
    }

    if (n > 1) res *= n - 1;
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);

    FOR(i,2,2000) if (!sieve[i]) {
        for(int j = i*i; j < MN; j += i)
            sieve[j] = i;
    }
    f[1] = 1;
    FOR(i,2,MN-1) {
        if (!sieve[i]) {
            pk[i] = make_pair(i, 1);
            f[i] = i-1;
        }
        else {
            int p = sieve[i];
            if (pk[i/p].first == p) {
                pk[i] = make_pair(p, pk[i/p].second + 1);
                f[i] = i / p * (p-1);
            }
            else {
                pk[i] = make_pair(-1, 0);
                int u = i, v = 1;
                while (u % p == 0) {
                    u /= p;
                    v *= p;
                }
                f[i] = f[u] * f[v];
            }
        }
    }
    int n, k;
    while (cin >> n >> k) {
        int turn = (k + 1) / 2;
        while (turn--) {
            n = getF(n);
            if (n == 1) break;
        }
        const int MOD = 1e9 + 7;
        cout << n % MOD << endl;
    }
}
