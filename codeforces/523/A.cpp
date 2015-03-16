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

int m, n;
char a[111][111], tmp[111][111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        swap(m, n);
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        // Rotate
        FOR(i,1,m) FOR(j,1,n) tmp[i][j] = a[i][j];
        FOR(i,1,n) FOR(j,1,m) a[i][j] = tmp[j][n-i+1]; swap(m, n);

        // Flip
        FOR(i,1,m) FOR(j,1,n) tmp[i][j] = a[i][j];
        FOR(i,1,m) FOR(j,1,n) a[i][j] = tmp[m-i+1][j];

        FOR(i,1,m) {
            FOR(j,1,n) cout << a[i][j] << a[i][j];
            cout << "\n";
            FOR(j,1,n) cout << a[i][j] << a[i][j];
            cout << "\n";
        }
    }
    return 0;
}
