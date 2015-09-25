
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int m, n;
char a[55][55];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        int res = 0;
        FOR(i,1,m-1) FOR(j,1,n-1) {
            char x[5];
            x[0] = a[i][j];
            x[1] = a[i][j+1];
            x[2] = a[i+1][j];
            x[3] = a[i+1][j+1];
            sort(x, x+4);

            if (x[0] == 'a' && x[1] == 'c' && x[2] == 'e' && x[3] == 'f')
                ++res;
        }
        cout << res << endl;
    }
}
