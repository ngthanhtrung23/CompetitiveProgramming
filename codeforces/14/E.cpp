
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

ll f[22][4][4][11][11];

int main() {
    ios :: sync_with_stdio(false);
    int n, t;
    while (cin >> n >> t) {
        memset(f, 0, sizeof f);
        REP(x,4) REP(y,4) if (x != y)
            f[2][x][y][0][0] = 1;

        FOR(i,2,n-1) REP(x,4) REP(y,4) FOR(up,0,t) FOR(down,0,t-1) {
            REP(z,4) if (z != y) {
                int up2 = up; if (y > x && y > z) up2++;
                int down2 = down; if (y < x && y < z) down2++;

                if (up2 <= t && down2 <= t-1) {
                    f[i+1][y][z][up2][down2] += f[i][x][y][up][down];
                }
            }
        }
        ll res = 0;
        REP(x,4) REP(y,4) if (x != y) res += f[n][x][y][t][t-1];
        cout << res << endl;
    }
}
