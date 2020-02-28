
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

int cnt[200111];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int la, lb;
    cin >> la >> lb;
    string a, b;
    cin >> a >> b;

    reverse(ALL(a));
    reverse(ALL(b));
    a = " " + a + " ";
    b = " " + b + " ";
    cnt[lb+1] = 0;
    FORD(i,lb,1) {
        cnt[i] = cnt[i+1] + (b[i] == '1');
    }

    const int MOD = 998244353;
    int res = 0, p2 = 1;
    FOR(i,1,la) {
        if (a[i] == '1') res = (res + p2 * cnt[i]) % MOD;
        p2 = (p2 * 2 % MOD);
    }
    cout << res << endl;
    return 0;
}
