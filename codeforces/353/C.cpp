
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

const int MN = 100111;
int f[MN][2];
int a[MN];

void update(int& f, int val) {
    f = max(f, val);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        string s; cin >> s; s = " " + s + " ";

        memset(f, -1, sizeof f);
        f[n+1][0] = 0;

        FORD(i,n+1,2) FOR(lower,0,1) {
            int ff = f[i][lower];
            if (ff < 0) continue;

            FOR(cur,0,lower ? 1 : s[i-1]-'0') {
                int lower2 = lower;
                if (cur == 0 && s[i-1] == '1') lower2 = 1;
                update(f[i-1][lower2], ff + cur * a[i-1]);
            }
        }
        int res = 0;
        FOR(lower,0,1) update(res, f[1][lower]);
        cout << res << endl;
    }
    return 0;
}
