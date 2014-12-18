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

const int MN = 411;
int m, n, a[MN][MN], f[MN][MN];
unsigned short last[MN][MN*MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        memset(last, 0, sizeof last);
        memset(f, 0, sizeof f);

        int res = 0;
        // We fix the bottom row
        FOR(bottom,1,m) {
            // last[j][val] = at column j, what is nearest row where a[row][j] == val
            
            // Then fix the left and right column of the result rectangle
            FORD(l,n,1) FOR(r,l,n) {
                // Calculate f[l][r] = top row
                if (l == r) f[l][r] = max(f[l][r], (int) last[l][a[bottom][l]]);
                else {
                    f[l][r] = max(f[l][r], max(f[l+1][r], f[l][r-1]));
                    f[l][r] = max(f[l][r], (int) max(last[l][a[bottom][r]], last[r][a[bottom][l]]));
                    if (a[bottom][l] == a[bottom][r]) f[l][r] = max(f[l][r], bottom);
                }
                res = max(res, (r - l + 1) * (bottom - f[l][r]));
            }

            FOR(j,1,n) last[j][a[bottom][j]] = bottom;
        }
        cout << res << endl;
    }
    return 0;
}

