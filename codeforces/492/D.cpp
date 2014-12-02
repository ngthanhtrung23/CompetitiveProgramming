#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n, x, y;
    while (cin >> n >> x >> y) {
        int cntx = 0, cnty = 0;
        vector<int> all;
        vector<int> sum;
        while (cntx < x || cnty < y) {
            // (cntx + 1) / x  vs  (cnty + 1) / y
            long long l = (cntx + 1LL) * y;
            long long r = (cnty + 1LL) * x;

            if (l == r) all.push_back(3), ++cntx, ++cnty;
            else if (l < r) all.push_back(1), ++cntx;
            else all.push_back(2), ++cnty;
        }
        sum.resize(all.size());
        REP(i,sum.size()) {
            if (i) sum[i] = sum[i-1];
            sum[i] += __builtin_popcount(all[i]);
        }
        while (n--) {
            int q; cin >> q;
            q %= (x + y);
            if (q == 0) cout << "Both" << endl;
            else {
                int first = lower_bound(sum.begin(), sum.end(), q) - sum.begin();
                if (all[first] == 3) cout << "Both" << endl;
                else if (all[first] == 1) cout << "Vanya" << endl;
                else cout << "Vova" << endl;
            }
        }
    }
    return 0;
}
