// nghi cham qua :'(
// duel RR vs ngfam
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

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int n;
    while (cin >> n) {
        if (n == 1) {
            cout << 1 << endl << 0 << endl;
            continue;
        }
        int cnt = 0;
        vector<int> p;
        for (int i = 2; i*i <= n; i++) {
            while (n % i == 0) {
                ++cnt;
                n /= i;
                if (SZ(p) < 3) p.push_back(i);
            }
        }
        if (n > 1) ++cnt;

        if (cnt == 1) {
            cout << 1 << endl << 0 << endl;
        } else if (cnt == 2) {
            cout << 2 << endl;
        } else {
            cout << 1 << endl << p[0] * p[1] << endl;
        }
    }
    return 0;
}
