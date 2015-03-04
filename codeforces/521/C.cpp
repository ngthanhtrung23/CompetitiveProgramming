
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

const ll MOD = 1e9 + 7;
const int MN = 200111;

ll gt[MN], inv_gt[MN], s[MN], sum[MN], sumdiv[MN], p10[MN], inv_p10[MN], sumsumdiv[MN];
int n, k;

ll power(ll x, ll k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    ll mid = power(x * x % MOD, k >> 1);
    if (k & 1) return mid * x % MOD;
    else return mid;
}

void init() {
    REP(i,MN) {
        if (i == 0) {
            gt[i] = inv_gt[i] = 1;
            p10[i] = inv_p10[i] = 1;
        }
        else {
            gt[i] = gt[i-1] * i % MOD;
            inv_gt[i] = power(gt[i], MOD - 2);
            p10[i] = p10[i-1] * 10 % MOD;
            inv_p10[i] = power(p10[i], MOD - 2);
        }
    }
}

ll C(int n, int k) {
    if (k > n || k < 0) return 0;
    return gt[n] * inv_gt[k] % MOD * inv_gt[n-k] % MOD;
}

ll getSum(int i, int j) {
    return (sum[i] - sum[j+1] + MOD) * inv_p10[n-j] % MOD;
}

char tmp[MN];

void update(ll& x, ll val) {
//    DEBUG(val);
    x = (x + val) % MOD;
}

int main() {
    init();
    while (scanf("%d%d\n", &n, &k) == 2) {
        gets(tmp);
        REP(i,n) s[i+1] = tmp[i] - '0';
        sum[n+1] = 0;
        sumdiv[n+1] = 0;
        sumsumdiv[n+1] = 0;
        FORD(i,n,1) {
            sum[i] = (sum[i+1] + s[i] * p10[n-i]) % MOD;
            sumdiv[i] = sum[i] * inv_p10[n-i+1] % MOD;
            sumsumdiv[i] = (sumsumdiv[i+1] + sumdiv[i]) % MOD;
        }

//        PR(s, n);
//        PR(sum, n);

        ++k;
        // k now becomes # numbers
        if (k == 1) {
            cout << sum[1] << endl;
            continue;
        }
        ll res = 0;
        FOR(len,1,n-1) {
//            DEBUG(len);
            // 1 --> len
            update(res, getSum(1, len) * C(n-len-1, k-2));

            // n-len+1 --> n
            int i = n - len + 1;
            update(res, getSum(i, n) * C(i-2, k-2));

            // i --> j
            if (k >= 3) {
                ll x = (sumsumdiv[2] - sumsumdiv[n-len+1] + MOD) * p10[len] % MOD;
                x = (x - sumsumdiv[2+len] + sumsumdiv[n+1] + MOD) % MOD;
                update(res, x * C(n-2-len, k-3) % MOD);
            }
        }
        cout << res << endl;
    }
    return 0;
}

