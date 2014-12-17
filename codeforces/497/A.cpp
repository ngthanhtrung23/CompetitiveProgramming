#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 1011;
int m, n;
char a[MN][MN];
bool eq[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        FOR(i,1,m-1) eq[i] = true;

        int res = 0;
        FOR(j,1,n) {
            int need = false;
            FOR(i,1,m-1) {
                if (eq[i] && a[i][j] > a[i+1][j]) need = true;
            }
            if (need) ++res;
            else {
                FOR(i,1,m-1)
                    if (a[i+1][j] > a[i][j]) eq[i] = false;
            }
        }
        cout << res << endl;
    }
    return 0;
}
