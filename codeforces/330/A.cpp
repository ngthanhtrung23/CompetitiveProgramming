
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
char a[111][111];
bool badRow[111], badCol[111];

int main() {
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        memset(badRow, false, sizeof badRow);
        memset(badCol, false, sizeof badCol);

        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'S') {
            badRow[i] = true;
            badCol[j] = true;
        }

        int res = 0;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') {
            if (!badRow[i] || !badCol[j]) ++res;
        }
        cout << res << endl;
    }
    return 0;
}
