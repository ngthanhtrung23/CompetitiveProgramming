#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 311;

char a[MN][MN];
int n;

bool check() {
    FOR(i,1,n) if (a[i][i] != a[1][1]) return false;
    FOR(i,1,n) if (a[i][n+1-i] != a[1][1]) return false;

    FOR(i,1,n) FOR(j,1,n)
    if (i != j && j != n-i+1) {
        if (a[i][j] == a[1][1] || a[i][j] != a[1][2]) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];
        if (check()) puts("YES");
        else puts("NO");
    }
    return 0;
}
