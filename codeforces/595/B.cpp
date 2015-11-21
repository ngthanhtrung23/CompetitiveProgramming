
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;
const ll MOD = 1e9 + 7;
int n, k;
int a[MN], b[MN];
ll p10[11];

ll get(ll bound, ll a) {
    if (bound < 0) return 0;
    bound -= bound % a;
    return bound / a + 1;
}

ll get(ll from, ll to, ll a) {
    ll res = get(to, a) - get(from-1, a);
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> k) {
        FOR(i,1,n/k) cin >> a[i];
        FOR(i,1,n/k) cin >> b[i];

        p10[0] = 1;
        FOR(i,1,10) p10[i] = p10[i-1] * 10LL;

        ll res = 1;
        FOR(i,1,n/k) {
            res = res * (get(0, p10[k] - 1, a[i])
                    - get(b[i] * p10[k-1], (b[i]+1) * p10[k-1] - 1, a[i]))
                % MOD;
        }
        cout << res << endl;
    }
}
