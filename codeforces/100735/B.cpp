
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

const ll MOD = 1e9 + 9;
int n, f[20];

struct Matrix {
    ll x[20][20];

    void print() {
        REP(i,n) {
            REP(j,n) cout << x[i][j] << ' ';
            cout << endl;
        }
    }
} I, trans, A[66];

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix c;
    REP(i,n) REP(j,n) {
        c.x[i][j] = 0;
        REP(k,n)
            c.x[i][j] = (c.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return c;
}

int main() {
    ios :: sync_with_stdio(false);
    ll m, c;
    while (cin >> n >> m >> c) {
        REP(i,n) cin >> f[i];
        --m;

        memset(A, 0, sizeof A);
        memset(I.x, 0, sizeof I.x);

        REP(i,n) I.x[i][i] = 1;
        REP(i,n-1) {
            A[0].x[i][i+1] = 1;
        }

        REP(i,c) {
            int u; cin >> u;
            A[0].x[n-1][n-u] = 1;
        }

        if (m < n) {
            cout << f[m] << endl;
            continue;
        }

        FOR(i,1,65) A[i] = A[i-1] * A[i-1];

        trans = I;
        REP(bit,63) if (((m-n+1) >> bit) & 1) {
            trans = trans * A[bit];
        }
        ll res = 0;
        REP(i,n) res = (res + f[i] * trans.x[n-1][i]) % MOD;
        cout << res << endl;
    }
}

