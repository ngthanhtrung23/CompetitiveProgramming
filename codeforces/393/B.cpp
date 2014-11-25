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

int n;
double a[211][211], b[211][211], w[211][211];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> w[i][j];

        FOR(i,1,n) a[i][i] = w[i][i];
        FOR(i,1,n) FOR(j,i+1,n) {
            a[j][i] = a[i][j] = (w[i][j] + w[j][i]) / 2.0;
            b[i][j] = w[i][j] - a[i][j];
            b[j][i] = w[j][i] - a[j][i];
        }
        FOR(i,1,n) {
            FOR(j,1,n) cout << a[i][j] << ' ';
            cout << endl;
        }
        FOR(i,1,n) {
            FOR(j,1,n) cout << b[i][j] << ' ';
            cout << endl;
        }
    }
    return 0;
}
