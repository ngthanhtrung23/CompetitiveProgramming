
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int main() {
    ios :: sync_with_stdio(false);
    string s;
    while (cin >> s) {
        s = " " + s;
        int q; cin >> q;
        while (q--) {
            int l, r, k; cin >> l >> r >> k;
            k %= (r - l + 1);
            if (k == 0) continue;

            string t = s;

            for(int i = l, j = r - k + 1; i <= r; ++i) {
                s[i] = t[j];
                ++j; if (j > r) j = l;
            }
        }
        cout << s.substr(1) << endl;
    }
}
