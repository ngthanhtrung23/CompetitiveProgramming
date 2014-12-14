#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MOD = 10003;
int f[111][55][55][55];

void add(int &x, int val) {
    x = (x + val) % MOD;
}

int main() {
    freopen("rooks.in", "r", stdin);
    freopen("rooks.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int m, n, k;
    while (cin >> m >> n >> k) {
        if (k > m*2 || k > n*2) {
            cout << 0 << endl;
            continue;
        }
        memset(f, 0, sizeof f);
        f[0][0][n][0] = 1;
        FOR(has,0,k) FOR(i,1,m) FOR(c2,0,n) FOR(c1,0,n-c2) if (f[has][i-1][c2][c1]) {
            int x = f[has][i-1][c2][c1];
            // c2, c2
            if (c2 >= 2) add(f[has+2][i][c2-2][c1+2], c2 * (c2 - 1) / 2 * x);
            // c2, c1
            if (c1 && c2) add(f[has+2][i][c2-1][c1], c2 * c1 * x);
            // c1, c1
            if (c1 >= 2) add(f[has+2][i][c2][c1-2], c1 * (c1 - 1) / 2 * x);

            // c2
            if (c2) add(f[has+1][i][c2-1][c1+1], x * c2);
            // c1
            if (c1) add(f[has+1][i][c2][c1-1], x * c1);
            // None
            add(f[has][i][c2][c1], x);
        }
        int res = 0;
        FOR(c2,0,n) FOR(c1,0,n-c2)
            add(res, f[k][m][c2][c1]);
        cout << res << endl;
    }
    return 0;
}
