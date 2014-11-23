#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int n, s[111], a[111][111], z[111], nz;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        int left = 0, right = 0;
        nz = 0;
        FOR(i,1,n) {
            cin >> s[i];
            FOR(j,1,s[i]) cin >> a[i][j];

            for(int u = 1, v = s[i]; u < v; ++u, --v) {
                left += a[i][u];
                right += a[i][v];
            }
            if (s[i] % 2 == 1) {
                z[++nz] = a[i][s[i]/2 + 1];
            }
        }
        sort(z+1, z+nz+1);
        int turn = 1;
        FORD(i,nz,1) {
            if (turn % 2 == 1) left += z[i];
            else right += z[i];

            ++turn;
        }
        cout << left << ' ' << right << endl;
    }
    return 0;
}