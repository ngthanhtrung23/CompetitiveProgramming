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

const int MN = 1011;
const int MOD = 1e9 + 7;

int c[MN][MN], a[MN];

int main() {
    ios :: sync_with_stdio(false);
    FOR(i,0,1000) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
    }
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        long long res = 1;
        int sum = 0;
        FOR(i,1,n) {
            res = res * c[sum+a[i]-1][a[i]-1] % MOD;
            sum += a[i];
        }
        cout << res << endl;
    }
}
