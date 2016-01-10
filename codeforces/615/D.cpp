
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;
const ll MOD = 1e9 + 7;

ll cnt[MN];
int n;

ll power(ll x, ll k) {
    ll res = 1;
    while (k > 0) {
        if (k & 1) res = res * x % MOD;
        x = x * x % MOD;
        k >>= 1;
    }
    return res;
}

ll l[MN], r[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) {
            int u; cin >> u;
            cnt[u]++;
        }
        l[0] = 1;
        FOR(i,1,MN-1) l[i] = l[i-1] * (cnt[i] + 1LL) % (MOD - 1);
        r[MN-1] = 1;
        FORD(i,MN-2,1) r[i] = r[i+1] * (cnt[i] + 1LL) % (MOD - 1);

        ll res = 1;
        FOR(i,1,MN-2) if (cnt[i]) {
            ll p = (cnt[i] * (cnt[i] + 1) / 2) % (MOD - 1);
            p = p * l[i-1] % (MOD - 1);
            p = p * r[i+1] % (MOD - 1);
            res = res * power(i, p) % MOD;
        }
        cout << res << endl;
    }
}
