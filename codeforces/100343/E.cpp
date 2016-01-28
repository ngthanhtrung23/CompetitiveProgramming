
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int n;
const int MN = 66;

ll f[MN][MN][MN][2][2];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("permutominoes.in", "r", stdin);
    freopen("permutominoes.out", "w", stdout);
    while (cin >> n) {
        memset(f, 0, sizeof f);
        f[1][1][2][0][0] = 1;
        FOR(y,1,n-2) FOR(x1,1,y) FOR(x2,1,y+1) REP(incl,2) REP(decr,2) {
            ll t = f[y][x1][x2][incl][decr];
            // reduce left
            if (!incl) {
                f[y+1][x1][x2+1][incl][decr] += t;
            }
            // increase right
            if (!decr) {
                f[y+1][x1][x2+1][incl][decr] += t;
            }
            // increase left
            FOR(to,x1+1,x2) {
                f[y+1][to][x2+1][1][decr] += t;
            }
            // reduce right
            FOR(to,x1+1,x2) {
                f[y+1][x1][to][incl][1] += t;
            }
        }
        ll res = 0;
        FOR(x1,1,n) FOR(x2,x1+1,n) REP(incl,2) REP(decr,2) {
            res += f[n-1][x1][x2][incl][decr];
        }
        cout << res << endl;
    }
}
