
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

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        int mini = m+1, maxi = 0, minj = n+1, maxj = 0;
        FOR(i,1,m) FOR(j,1,n) {
            cin >> a[i][j];
            if (a[i][j] == '*') {
                mini = min(mini, i);
                maxi = max(maxi, i);
                minj = min(minj, j);
                maxj = max(maxj, j);
            }
        }
        FOR(i,mini,maxi) {
            FOR(j,minj,maxj) cout << a[i][j];
            cout << endl;
        }
    }
    return 0;
}
