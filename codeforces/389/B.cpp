#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

char a[111][111];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];

        bool good = true;
        FOR(i,1,n) FOR(j,1,n) if (a[i][j] == '#') {
            if (a[i+1][j-1] == '#' && a[i+1][j] == '#' && a[i+1][j+1] == '#' && a[i+2][j] == '#') {
                a[i+1][j-1] = a[i+1][j] = a[i+1][j+1] = a[i+2][j] = '.';
            }
            else good = false;
        }
        if (good) puts("YES"); else puts("NO");
    }
    return 0;
}
