
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
using namespace std;

const int MN = 411;

int f[2][MN][MN], a[MN], b[MN];

int main() {
    ios :: sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        FOR(i,1,m) cin >> a[i];
        FOR(i,1,m) cin >> b[i];
        
        REP(i,2) REP(j,MN) REP(k,MN) f[i][j][k] = 1e9 + 7;

        int up = n / 2, down = n - up;
        f[0][0][0] = 0;
        FOR(i,1,m) {
            int t = i % 2;
            FOR(x,0,down) FOR(y,0,down) {
                f[t][x][y] = f[1-t][x][y];
                if (x > 0) f[t][x][y] = min(f[t][x][y], f[1-t][x-1][y] + a[i]);
                if (y > 0) f[t][x][y] = min(f[t][x][y], f[1-t][x][y-1] + b[i]);
            }
        }
        cout << min(f[m % 2][up][down], f[m % 2][down][up]) << endl;
    }
}
