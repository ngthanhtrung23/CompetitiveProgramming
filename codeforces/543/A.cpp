
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

int MOD;

int f[2][511][511];
int a[511];

void update(int& x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios :: sync_with_stdio(false);
    int n, m, b;
    while (cin >> n >> m >> b >> MOD) {
        FOR(i,1,n) cin >> a[i];

        memset(f, 0, sizeof f);
        f[1][0][0] = 1;
        FOR(i,1,n) {
            int cur = i%2;
            memset(f[1-cur], 0, sizeof f[1-cur]);

            FOR(j,0,m) FOR(k,0,b) if (f[cur][j][k]) {
                update(f[cur^1][j][k], f[cur][j][k]);
                if (k+a[i] <= b) update(f[cur][j+1][k+a[i]], f[cur][j][k]);
            }
        }
        int res = 0;
        FOR(bug,0,b) update(res, f[n%2][m][bug]);
        cout << res << endl;
    }
    return 0;
}
