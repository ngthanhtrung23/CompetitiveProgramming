
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
using namespace std;

const int MOD = 1e9 + 7;
const int MN = 4011;

int f[MN][MN][2];
int n;

void add(int& x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        memset(f, 0, sizeof f);
        f[0][0][0] = 1;
        FOR(i,0,n-1) FOR(c,0,i) FOR(t,0,1) if (f[i][c][t]) {
            int cur = f[i][c][t];
            // lonely element
            add(f[i+1][c][1], cur);

            // put in a class
            add(f[i+1][c][t], cur * (ll) c % MOD);

            // put in a new class
            add(f[i+1][c+1][t], cur);
        }
        int res = 0;
        FOR(c,0,n) add(res, f[n][c][1]);
        cout << res << endl;
    }
}
