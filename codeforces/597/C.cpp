
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
using namespace std;

const int MN = 100111;
const int MK = 11;

ll bit[MK][MN], f[MK][MN];

#define _(X) ((X) & (-(X)))

void update(int t, int u, ll val) {
    while (u < MN) {
        bit[t][u] += val;
        u += _(u);
    }
}

ll get(int t, int u) {
    ll res = 0;
    while (u > 0) {
        res += bit[t][u];
        u -= _(u);
    }
    return res;
}

int a[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, k;
    while (cin >> n >> k) {
        memset(f, 0, sizeof f);
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            cin >> a[i];
            f[0][i] = 1;
        }
//        PR(a, n);
//        PR(f[0], n);

        FOR(turn,1,k) {
            FOR(i,1,n) {
                f[turn][i] = get(turn-1, a[i] - 1);
                update(turn-1, a[i], f[turn-1][i]);
            }
//            PR(f[turn], n);
        }
        ll res = 0;
        FOR(i,1,n) res += f[k][i];
        cout << res << endl;
    }
}
