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

const int MN = 100111;
int n, k, q;
string s;
int sum[MN], sumk[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k >> q) {
        cin >> s;
        s = " " + s;
        FOR(i,1,n) {
            sum[i] = sum[i-1];
            sumk[i] = (i >= k) ? sumk[i-k] : 0;
            if (s[i] == '1') ++sumk[i], ++sum[i];
        }
//        PR(sum, n);
//        PR(sumk, n);

        while (q--) {
            int l, r; cin >> l >> r;
            int all = r - l + 1;
            int good = (r - (l+k-1)) / k + 1;
            int bad = all - good;

            int res = 0;
            // At good position: 0 --> 1
            res += good - (sumk[r] - sumk[l-1]);
            // At bad position: 1 --> 0
            res += (sum[r] - sum[l-1]) - (sumk[r] - sumk[l-1]);
            cout << res << endl;
        }
    }
    return 0;
}
