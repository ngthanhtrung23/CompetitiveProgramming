
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

int n, a[211], sum[211], has[2];
int f[2][211][40111];

void update(int& x, int val) {
    x = min(x, val);
}

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    while (cin >> n) {
        cin >> has[0] >> has[1];
        FOR(i,1,n) {
            cin >> a[i];
            sum[i] = sum[i-1] + a[i];
        }
        REP(t,2) FOR(i,0,n) FOR(j,0,40000) f[t][i][j] = 1000111000;

        f[0][0][0] = f[1][0][0] = 0;
        FOR(i,0,n-1) REP(t,2) FOR(p0,0,40000) if (f[t][i][p0] < 1000111000) {
            int h0 = has[0] - p0;
            int h1 = has[1] - (sum[i] - p0);

            if (h0 >= a[i+1]) {
                update(f[0][i+1][p0 + a[i+1]], f[t][i][p0] + ((t == 0) ? 0 : min(a[i], a[i+1])));
            }
            if (h1 >= a[i+1]) {
                update(f[1][i+1][p0], f[t][i][p0] + ((t == 1) ? 0 : min(a[i], a[i+1])));
            }
        }
        int res = 1000111000;
        REP(t,2) FOR(p0,0,40000) res = min(res, f[t][n][p0]);
        if (res == 1000111000) res = -1;
        cout << res << endl;
    }
    return 0;
}
