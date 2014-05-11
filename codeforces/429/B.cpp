#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 1011;
const int oo = 1000111000;

int m, n;
int a[MN][MN];
int f1[MN][MN], f2[MN][MN], f3[MN][MN], f4[MN][MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        FOR(i,0,m+1) FOR(j,0,n+1) f1[i][j] = f2[i][j] = f3[i][j] = f4[i][j] = -oo;

        FOR(i,1,m) FOR(j,1,n) {
            if (i == 1 && j == 1) f1[i][j] = a[i][j];
            else f1[i][j] = max(f1[i-1][j], f1[i][j-1]) + a[i][j];
        }
        FOR(i,1,m) FORD(j,n,1) {
            if (i == 1 && j == n) f2[i][j] = a[i][j];
            else f2[i][j] = max(f2[i-1][j], f2[i][j+1]) + a[i][j];
        }
        FORD(i,m,1) FOR(j,1,n) {
            if (i == m && j == 1) f3[i][j] = a[i][j];
            else f3[i][j] = max(f3[i+1][j], f3[i][j-1]) + a[i][j];
        }
        FORD(i,m,1) FORD(j,n,1) {
            if (i == m && j == n) f4[i][j] = a[i][j];
            else f4[i][j] = max(f4[i+1][j], f4[i][j+1]) + a[i][j];
        }

        int res = 0;
        FOR(i,2,m-1) FOR(j,2,n-1) {
            res = max(res, f1[i-1][j] + f2[i][j+1] + f3[i][j-1] + f4[i+1][j]);
            res = max(res, f1[i][j-1] + f2[i-1][j] + f3[i+1][j] + f4[i][j+1]);
        }
        cout << res << endl;
    }
    return 0;
}
