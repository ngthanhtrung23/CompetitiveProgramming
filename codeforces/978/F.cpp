
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()

const int MN = 200111;
int a[MN], c[MN], res[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int n, m;
    while (cin >> n >> m) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) c[i] = a[i];
        sort(c+1, c+n+1);
        int nc = n;
        FOR(i,1,n) a[i] = lower_bound(c+1, c+nc+1, a[i]) - c;

        FOR(i,1,n) res[i] = a[i] - 1;

        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            if (a[u] > a[v]) --res[u];
            if (a[v] > a[u]) --res[v];
        }

        FOR(i,1,n) cout << res[i] << ' '; cout << '\n';
    }
    return 0;
}
