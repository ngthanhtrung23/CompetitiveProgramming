
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

char a[11][11];

bool ok() {
    FOR(i,1,9)
        FOR(j1,1,9) FOR(j2,j1+1,9)
            if (a[i][j1] == a[i][j2])
                return false;

    FOR(j,1,9)
        FOR(i1,1,9) FOR(i2,i1+1,9)
            if (a[i1][j] == a[i2][j])
                return false;

    for(int u=1; u <= 9; u += 3)
        for(int v = 1; v <= 9; v += 3)
            FOR(i1,u,u+2) FOR(j1,v,v+2)
                FOR(i2,i1,u+2) FOR(j2,v,v+2)
                if (i1 != i2 || j1 != j2)
                    if (a[i1][j1] == a[i2][j2])
                        return false;

    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    int test; cin >> test;
    while (test--) {
        FOR(i,1,9) FOR(j,1,9) cin >> a[i][j];

        if (ok()) cout << "Valid" << endl;
        else cout << "Invalid" << endl;
    }
    return 0;
}
