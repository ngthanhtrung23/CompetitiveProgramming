
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

int n, k, a[111], b[111];
int f[111][220111];

void update(int& x, int val) {
    x = max(x, val);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) cin >> b[i];
        
        FOR(i,1,n) a[i] = a[i] - k * b[i];
        const int ZERO = 110000;

        memset(f, -1, sizeof f);
        f[0][ZERO] = 0;

        FOR(i,0,n-1) FOR(cur,0,220022) if (f[i][cur] >= 0) {
            update(f[i+1][cur], f[i][cur]);
            update(f[i+1][cur + a[i+1]], f[i][cur] + b[i+1]);
        }
        int res = f[n][ZERO];
        if (res == 0) cout << -1 << endl;
        else cout << res * k << endl;
    }
    return 0;
}
