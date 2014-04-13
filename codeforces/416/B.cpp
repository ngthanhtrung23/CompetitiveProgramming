#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int m, n;
int a[50111][11], t[50111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        memset(t, 0, sizeof t);
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        FOR(j,1,n) {
            FOR(i,1,m) {
                t[i] = max(t[i-1], t[i]) + a[i][j];
            }
        }

        FOR(i,1,m) cout << t[i] << endl;
    }
    return 0;
}
