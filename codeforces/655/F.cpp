#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
#define div div____
using namespace std;

const int MN = 2000111;
int n, k, q;
int a[MN], sieve[MN];

void init() {
    FOR(i,2,1000) if (!sieve[i]) {
        for(int j = i*i; j < MN; j += i)
            sieve[j] = i;
    }
}

int dp[111], dk[111];
vector<int> div;
void attempt(int i, int nd, int prod) {
    if (i > nd) {
        div.push_back(prod);
        return ;
    }
    int cur = 1;
    FOR(power,0,dk[i]) {
        attempt(i+1, nd, prod * cur);
        cur *= dp[i];
    }
}
vector<int> divisors(int x) {
    int nd = 0;
    while (x > 1) {
        int p = (sieve[x] ? sieve[x] : x);
        ++nd;
        dp[nd] = p;
        dk[nd] = 0;
        while (x % p == 0) {
            x /= p;
            ++dk[nd];
        }
    }
    div.clear();
    attempt(1, nd, 1);
    return div;
}

const int MOD = 1e9 + 7;
int res[MN];
int ls[MN];

void resetAll() {
    memset(res, 0, sizeof res);
    memset(ls, 0, sizeof ls);
}

ll add[MN];
ll gt[MN], inv_gt[MN];

int power(int x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;

    ll mid = power(x, k >> 1);
    mid = mid * mid % MOD;

    if (k & 1) return mid * x % MOD;
    return mid;
}
int inverse(int x) {
    return power(x, MOD - 2);
}

ll C(int n, int k) {
    return gt[n] * inv_gt[k] % MOD * inv_gt[n-k] % MOD;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    init();

    gt[0] = 1; FOR(i,1,MN-1) gt[i] = gt[i-1] * i % MOD;
    REP(i,MN) inv_gt[i] = inverse(gt[i]);

    while (scanf("%d%d%d", &n, &k, &q) == 3) {
        FOR(i,1,n+q) scanf("%d", &a[i]);
        resetAll();

        FOR(g,1,1000*1000) {
            add[g] = g;
            auto d = divisors(g);
            for(int x : d) if (x < g) {
                add[g] = (add[g] - add[x] + MOD) % MOD;
            }
        }

        FOR(i,1,n+q) {
            auto d = divisors(a[i]);
            for(int x : d) {
                if (ls[x] >= k-1) {
                    res[i] = (res[i] + C(ls[x], k-1) * add[x]) % MOD;
                }
                ++ls[x];
            }
        }
        FOR(i,1,n+q) {
            res[i] = (res[i-1] + res[i]) % MOD;
        }
        FOR(i,n+1,n+q) printf("%d\n", res[i]);
    }
}
