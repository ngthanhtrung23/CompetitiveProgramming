
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

const int MN = 3011;
int n, a[MN], b[MN], c[MN], sumb[MN];
int f[2][MN];

void update(int& x, int val) {
    x = max(x, val);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) {
            cin >> b[i];
            sumb[i] = sumb[i-1] + b[i];
        }
        FOR(i,1,n) cin >> c[i];
        if (n == 1) {
            cout << a[1] << endl;
            continue;
        }
        if (n == 2) {
            cout << max(a[1] + b[2], a[2] + b[1]) << endl;
            continue;
        }
        memset(f, -0x3f, sizeof f);
        FOR(i,1,n) {
            f[0][i] = sumb[i-1] + a[i];
            FOR(j,1,i-1)
                update(f[0][i], f[1][j] + sumb[i-1] - sumb[j] + a[i]);

            FOR(j,1,i-1)
                update(f[1][i], f[0][j] + sumb[i-1] - sumb[j] + c[i]);
        }
        int res = -1000111000;
        FOR(i,1,n)
            update(res, f[0][i] + sumb[n] - sumb[i]);
        cout << res << endl;
    }
}
