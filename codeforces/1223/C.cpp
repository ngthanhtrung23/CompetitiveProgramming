
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
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        vector<int> prices(n);
        for(int& x : prices) {
            cin >> x;
            x /= 100;
        }
        sort(ALL(prices));
        reverse(ALL(prices));

        int x, a; cin >> x >> a;
        int y, b; cin >> y >> b;
        int required; cin >> required;

        if (x < y) {
            swap(x, y);
            swap(a, b);
        }

        auto check = [prices, x, a, y, b, required] (int sold) -> bool {
            int mod_xy = sold / lcm(a, b);
            int mod_x = sold / a - mod_xy;
            int mod_y = sold / b - mod_xy;

            int has = 0;
            for (auto p : prices) {
                if (mod_xy > 0) {
                    has += p * (x + y);
                    mod_xy--;
                } else if (mod_x > 0) {
                    has += p * x;
                    mod_x--;
                } else if (mod_y > 0) {
                    has += p * y;
                    mod_y--;
                }
            }
            return has >= required;
        };

        int l = 0, r = n, res = n + 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            } else l = mid + 1;
        }
        if (res == n+1) cout << -1; else cout << res;
        cout << '\n';
    }
    return 0;
}
