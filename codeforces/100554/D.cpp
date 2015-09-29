
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

double f[2511][55][55];

int m, n;

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> m >> n;
        f[0][0][0] = 1.0;

        FOR(k,0,m*n-1) FOR(i,0,m) FOR(j,0,n)
            if (f[k][i][j] > 1e-100) {
                if (i == m && j == n) continue;

                int empty = m*n - k;

                int p1 = i*j - k;
                int p2 = i*(n-j);
                int p3 = (m-i)*j;
                int p4 = (m-i)*(n-j);

                double cur = f[k][i][j];
                f[k+1][i][j] += cur * p1 / empty;
                f[k+1][i][j+1] += cur * p2 / empty;
                f[k+1][i+1][j] += cur * p3 / empty;
                f[k+1][i+1][j+1] += cur * p4 / empty;
            }

        double res = 0.0;
        FOR(k,1,m*n)
            res += f[k][m][n] * k;

        cout << (fixed) << setprecision(9) << res << endl;

        FOR(i,0,m*n) FOR(j,0,m) FOR(k,0,n) f[i][j][k] = 0.0;
    }
}
