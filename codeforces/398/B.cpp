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

const int MN = 2011;

int n;
double f[MN][MN];
bool rows[MN], cols[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        int row = n, col = n;
        memset(rows, true, sizeof rows);
        memset(cols, true, sizeof cols);
        int q; cin >> q;
        while (q--) {
            int u, v; cin >> u >> v;
            if (rows[u]) rows[u] = false, --row;
            if (cols[v]) cols[v] = false, --col;
        }
        f[0][0] = 0;
        FOR(i,1,n) f[i][0] = f[0][i] = f[i-1][0] + n / (double) i;
        double nn = n * n;
        FOR(x,1,n) FOR(y,1,n) {
            f[x][y] = (1 + (n-x)*y/nn * f[x][y-1] + x*(n-y)/nn * f[x-1][y] + x*y/nn * f[x-1][y-1]) / (1 - (n-x)*(n-y)/nn);
        }
        cout << f[row][col] << endl;
    }
    return 0;
}
