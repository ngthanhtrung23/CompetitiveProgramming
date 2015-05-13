
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

int f[2][10111000];

int main() {
    ios :: sync_with_stdio(false);
    f[0][0] = 1;
    FOR(i,1,10000 * 1000) {
        f[0][i] = f[1][i-1];
        f[1][i] = (f[0][i-1] * 3LL + f[1][i-1] * 2) % 1000000007;
    }
    int n;
    while (cin >> n) cout << f[0][n] << endl;
    return 0;
}

