#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;
const long long MOD = 1000000007;

long long power(long long x, long long k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x, k >> 1);
    mid = (mid * mid) % MOD;

    if (k & 1) return mid * x % MOD;
    else return mid;
}

inline long long inverse(long long x) {
    return power(x, MOD - 2);
}

long long gt[MN], rev_gt[MN];

long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (gt[n] * inverse(gt[k])) % MOD * inverse(gt[n-k]) % MOD;
}

int sieve[MN], cnt[MN];

void init() {
    sieve[1] = 1;
    for(int i=2; i*i <= 100000; ++i) if (!sieve[i]) {
        int j = i*i;
        while (j < MN) {
            sieve[j] = i;
            j += i;
        }
    }

    cnt[1] = 0;
    FOR(i,2,100000) {
        int u = i;
        while (sieve[u]) {
            int t = u / sieve[u];
            if (t % sieve[u] == 0) {
                cnt[i] = -1;
                break;
            }
            u = t;
            ++cnt[i];
        }
        if (cnt[i] >= 0) ++cnt[i];
    }

    // FOR(i,1,100000)
    // if (cnt[i] >= 0) {
    //     cout << i << ' ' << cnt[i] << endl;
    // }
}

void update(long long &res, int n, int f, int x) {
    if (cnt[x] < 0) return ;
    if (cnt[x] % 2 == 0) res = (res + C(n-1, f-1)) % MOD;
    else res = (res - C(n-1, f-1) + MOD) % MOD;

    // cout << n << ' ' << f << ' ' << res << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    gt[0] = 1;
    FOR(i,1,100000) gt[i] = (gt[i-1] * i) % MOD;
    FOR(i,0,100000) rev_gt[i] = inverse(gt[i]);

    init();

    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n, f; cin >> n >> f;

        if (f == 1) {
            if (n == 1) cout << 1 << endl;
            else cout << 0 << endl;
            continue;
        }

        long long res = 0;
        for(int i = 1; i*i <= n; ++i) if (n % i == 0) {
            update(res, n / i, f, i);
            if (i * i != n) update(res, i, f, n/i);
        }
        cout << res % MOD << endl;
    }
    return 0;
}
