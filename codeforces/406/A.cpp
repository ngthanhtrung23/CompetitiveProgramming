#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 1011;

int n, a[MN][MN], val[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];

        int sum = 0;
        FOR(i,1,n) {
            val[i] = a[i][i];
            sum ^= val[i];
        }

        int q; cin >> q;
        while (q--) {
            int typ; cin >> typ;
            if (typ == 3) {
                if (sum) putchar('1');
                else putchar('0');
            }
            else {
                int u; cin >> u;
                sum ^= val[u];
                val[u] = 1 - val[u];
                sum ^= val[u];
            }
        }
        puts("");
    }
    return 0;
}
