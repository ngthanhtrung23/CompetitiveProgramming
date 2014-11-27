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

int n, a[1011][1011], sum[1011][1011], f[1011][1011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n && n) {
        FOR(i,1,n) FOR(j,1,i) {
            cin >> a[i][j];
        }
        FOR(j,1,n) FOR(i,j,n) {
            int ii = i - j + 1;
            sum[j][ii] = sum[j][ii-1] + a[i][j];
        }
        memset(f, 0, sizeof f);
        FOR(j,1,n) {
            int ln = n - j + 1;
            FORD(k,ln,0) {
                f[j][k] = f[j-1][k] + sum[j][k];
                if (k < ln) f[j][k] = max(f[j][k], f[j][k+1]);
            }
//            PR0(f[j], ln+1);
        }
        cout << f[n][0] << endl;
    }
    return 0;
}
