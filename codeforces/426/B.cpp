#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int m, n, a[111][111];

bool check(int m) {
    FOR(i,1,m) FOR(j,1,n) {
        if (a[i][j] != a[m+m-i+1][j]) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        int res = m;
        while (m % 2 == 0) {
            m /= 2;
            if (check(m)) {
                res = m;
            }
            else break;
        }
        cout << res << endl;
    }
    return 0;
}
