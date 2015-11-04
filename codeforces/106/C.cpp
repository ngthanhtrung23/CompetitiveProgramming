
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

const int MN = 1011;
int f[22][MN];

int nDough, nStuff, c0, d0;
int a[MN], b[MN], c[MN], d[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> nDough >> nStuff >> c0 >> d0) {
        FOR(i,1,nStuff) cin >> a[i] >> b[i] >> c[i] >> d[i];

        memset(f, 0, sizeof f);
        int can = nDough / c0;
        // do not use any stuffing
        FOR(i,0,can) {
            f[0][i * c0] = i * d0;
        }
        FOR(i,1,nDough)
            f[0][i] = max(f[0][i], f[0][i-1]);

        // use some stuffing
        FOR(i,1,nStuff) {
            FOR(j,0,nDough)
                f[i][j] = f[i-1][j];

            FOR(j,0,nDough) {
                int can = min(j / c[i], a[i] / b[i]);
                FOR(x,0,can) {
                    f[i][j] = max(f[i][j], f[i-1][j - x * c[i]] + x * d[i]);
                }
            }

            FOR(j,1,nDough)
                f[i][j] = max(f[i][j], f[i][j-1]);
        }
        int res = 0;
        FOR(i,0,nStuff)
            res = max(res, f[i][nDough]);
        cout << res << endl;
    }
}

