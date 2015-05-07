
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

int a[111][111];

int main() {
    ios :: sync_with_stdio(false);
    int n, k;
    while (cin >> n >> k) {
        FOR(i,1,n) FOR(j,1,n) {
            if ((i+j) % 2 == 0) {
                if (k > 0) a[i][j] = 1, --k;
                else a[i][j] = 0;
            }
            else a[i][j] = 0;
        }
        if (k > 0) {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
        FOR(i,1,n) {
            FOR(j,1,n) if (a[i][j]) cout << 'L'; else cout << 'S';
            cout << endl;
        }
    }
    return 0;
}
