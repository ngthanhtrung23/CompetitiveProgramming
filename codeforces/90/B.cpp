
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
int has[2][111][311];

int main() {
    while (cin >> m >> n) {
        memset(has, 0, sizeof has);
        FOR(i,1,m) FOR(j,1,n) {
            cin >> a[i][j];
            has[0][i][a[i][j]]++;
            has[1][j][a[i][j]]++;
        }
        FOR(i,1,m) FOR(j,1,n)
            if (has[0][i][a[i][j]] == 1 && has[1][j][a[i][j]] == 1)
                cout << a[i][j];
        cout << endl;
    }
    return 0;
}
