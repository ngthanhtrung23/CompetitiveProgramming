
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

bitset<111> a[111];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) {
            a[i].reset();
            int k; cin >> k;
            while (k--) {
                int u; cin >> u;
                a[i].set(u);
            }
        }
        
        FOR(i,1,n) {
            bool ok = true;
            FOR(j,1,n) if (j != i) {
                bitset<111> t = a[j] & a[i];
                if (t == a[j]) {
                    ok = false;
                    break;
                }
            }
            cout << (ok ? "YES" : "NO") << endl;
        }
    }
    return 0;
}
