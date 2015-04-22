
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

int n, c[311][311], d[311][311];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) {
            cin >> c[i][j];
            d[i][j] = c[i][j];
        }
        FOR(k,1,n)
            FOR(i,1,n) FOR(j,1,n)
                c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

        bool ok = true;
        FOR(i,1,n) FOR(j,1,n)
            if (c[i][j] != d[i][j]) ok = false;

        if (ok) {
            FOR(i,1,n) {
                FOR(j,1,n) cout << c[i][j] << ' ';
                cout << endl;
            }
        }
        else cout << -1 << endl;
    }
    return 0;
}
