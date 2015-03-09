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

const int MN = 5011;

int n, h[MN], f[MN][MN], sum[MN];

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            scanf("%d", &h[i]);
            sum[i] = sum[i-1] + h[i];
        }

        FOR(i,1,n+2) FOR(j,1,n+2) f[i][j] = 1000111000;
        // f[i][j] = min height of last tower if we use 1..i to create at least j towers
        // --> f[i] is increasing function
        FOR(i,1,n-1) {
            f[i][1] = sum[i];
            FORD(k,i,1) f[i][k] = min(f[i][k], f[i][k+1]);
            // now we use f[i][k] to update all f[j][k+1]
            int k = 1;
            FOR(j,i+1,n) {
                while (sum[j] - sum[i] >= f[i][k+1]) ++k;
                if (sum[j] - sum[i] >= f[i][k]) {
                    f[j][k+1] = min(f[j][k+1], sum[j] - sum[i]);
                }
            }
        }
        int res = n-1;
        FOR(k,1,n) if (f[n][k] < 1000111000) {
            res = min(n - k, res);
        }
        cout << res << endl;
    }
    return 0;
}

