#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const ll MOD = 1000000007;
const int MN = 1000111;
int n, a[MN], cnt[MN];
ll gt[MN];

#define _(X) ((X) & (-(X)))

int get(int x) {
    int res = 0;
    while (x > 0) {
        res += cnt[x];
        x -= _(x);
    }
    return res;
}

void update(int x, int val) {
    while (x <= n) {
        cnt[x] += val;
        x += _(x);
    }
}

ll power(ll x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    ll mid = power(x*x%MOD, k>>1);
    if (k & 1) return mid * x % MOD;
    else return mid;
}

ll inverse(ll x) {
    return power(x, MOD-2);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    gt[0] = 1;
    FOR(i,1,1000 * 1000) gt[i] = (gt[i-1] * i) % MOD;
    ll inv4 = inverse(4);
    ll inv2 = inverse(2);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        ll res = 0;
        // Permutation a
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) {
            res = (res + get(n) - get(a[i]) + MOD) % MOD;
            update(a[i], 1);
        }
        // Consider permutation less than a
        memset(cnt, 0, sizeof cnt);
        int prefix = 0;
        ll half = 0;
        FOR(i,1,n) {
            // Consider permutations P with prefix == a(1..i-1)
            // P(i) < a(i)
            // suffix can be anything

//            DEBUG(i);
            
            // Number of different values we can place at position i
            ll nValues = (a[i] - 1) - get(a[i] - 1);
//            DEBUG(nValues);

            // Inversion in prefix 1..i-1
            res = (res + prefix * nValues % MOD * gt[n-i]) % MOD;
//            DEBUG(prefix);
//            DEBUG(res);
            
            // Inversion in suffix i+1..n
            ll len = n-i;
            ll suffix = len * (len-1) % MOD * gt[len] % MOD * inv4 % MOD;
            res = (res + nValues * suffix) % MOD;
//            DEBUG(suffix);
//            DEBUG(res);

            // Inversion (u, v) where u in [1, i] and v in [i+1, n]
            // first, if u in [1, i-1]
            res = (res + half * nValues % MOD * gt[n-i]) % MOD;
            // second, if u == i
            res = (res + nValues * (nValues-1) % MOD * gt[len] % MOD * inv2) % MOD;

//            DEBUG(res);
            prefix = (prefix + get(n) - get(a[i]) + MOD) % MOD;

            half = (half - get(n) + get(a[i]) + MOD) % MOD;
            half = (half + (a[i] - 1) - get(a[i] - 1) + MOD) % MOD;
            update(a[i], 1);
        }
        cout << res << endl;
//        DEBUG("OK");
    }
    return 0;
}

