
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

int n1, n2, k1, k2;
int f[111][111][2][12];
const int MOD = 100000000;

void update(int& x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

int main() {
    while (cin >> n1 >> n2 >> k1 >> k2) {
        memset(f, 0, sizeof f);
        f[0][0][0][0] = 1;
        FOR(i,0,n1) FOR(j,0,n2) REP(last,2) FOR(t,0,10) if (f[i][j][last][t]) {
            int cur = f[i][j][last][t];
            if (i < n1) {
                if (last == 1) update(f[i+1][j][0][1], cur);
                else if (t < k1) update(f[i+1][j][0][t+1], cur);
            }
            if (j < n2) {
                if (last == 0) update(f[i][j+1][1][1], cur);
                else if (t < k2) update(f[i][j+1][1][t+1], cur);
            }
        }
        int res = 0;
        REP(last,2) FOR(t,0,10) update(res, f[n1][n2][last][t]);
        cout << res << endl;
    }
    return 0;
}
