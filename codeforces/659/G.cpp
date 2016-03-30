
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

const int MN = 1000111;
const int MOD = 1e9 + 7;
int h[MN], n;

struct DP {
    int l, r, mult;

    DP() {}
    DP(int l, int r, int mult) : l(l), r(r), mult(mult) {
        if (l > r) {
            l = 1;
            r = 0;
            mult = 0;
        }
    }

    int get() {
        if (l > r) return 0;
        return (r - l + 1LL) * mult % MOD;
    }
    int get(int lower) {
        if (l >= lower) return get();
        return (r - lower + 1LL) * mult % MOD;
    }
} endsAt[MN], toLeft[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%lld", &n) == 1) {
        FOR(i,1,n) scanf("%lld", &h[i]);

        endsAt[1] = DP(1, h[1] - 1, 1);
        toLeft[1] = DP(1, 0, 0);

        FOR(i,2,n) {
            endsAt[i] = DP(1, h[i] - 1, 1);

            if (h[i] >= h[i-1]) {
                toLeft[i] = DP(h[i] - h[i-1] + 1, h[i] - 1,
                        (endsAt[i-1].get() + toLeft[i-1].get()) % MOD
                        );
            }
            else {
                toLeft[i] = DP(1, h[i] - 1,
                        (endsAt[i-1].get(h[i-1] - h[i] + 1) + toLeft[i-1].get(h[i-1] - h[i] + 1)) % MOD
                        );
            }
        }
        int res = 0;
        FOR(i,1,n) {
            res = (res + endsAt[i].get()) % MOD;
            res = (res + toLeft[i].get()) % MOD;
        }
        cout << res << endl;
    }
}
