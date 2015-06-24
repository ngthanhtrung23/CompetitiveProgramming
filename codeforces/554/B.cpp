
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

int n;
char a[111][111], b[111][111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];
        FOR(i,1,n) FOR(j,1,n) b[i][j] = a[i][j];
        int res = 0;
        FOR(i,1,n) {
            // make row i all 1
            FOR(i,1,n) FOR(j,1,n) a[i][j] = b[i][j];

            FOR(j,1,n) if (a[i][j] == '0') {
                // revert column j
                FOR(ii,1,n) if (a[ii][j] == '0') a[ii][j] = '1'; else a[ii][j] = '0';
            }

            // count how many rows
            int cnt = 0;
            FOR(ii,1,n) {
                bool ok = true;
                FOR(j,1,n) ok = ok && a[ii][j] == '1';
                if (ok) ++cnt;
            }
            res = max(res, cnt);
        }
        cout << res << endl;
    }
}
