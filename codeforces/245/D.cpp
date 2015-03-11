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

int a[111], b[111][111];
int n;

int main() {
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> b[i][j];
        FOR(i,1,n) {
            a[i] = 0;
            FOR(j,1,n) if (i != j) a[i] |= b[i][j];
        }
        FOR(i,1,n) cout << a[i] << ' '; cout << endl;
    }
    return 0;
}

