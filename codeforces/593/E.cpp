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

const ll MOD = 1e9 + 7;

int sz;
struct Matrix {
    ll x[22][22];

    void print() {
        REP(i,sz) {
            REP(j,sz) cout << x[i][j] << ' '; cout << endl;
        }
        cout << endl;
    }
} A, I;

struct Vector {
    ll x[22];

    void print() {
        PR0(x, sz);
    }
} f;

Vector update(const Vector& f, const Matrix& A) {
    Vector res;
    REP(i,sz) {
        res.x[i] = 0;
        REP(j,sz)
            res.x[i] = (res.x[i] + A.x[i][j] * f.x[j]) % MOD;
    }
    return res;
}

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    REP(i,sz) REP(j,sz) {
        res.x[i][j] = 0;
        REP(k,sz)
            res.x[i][j] = (res.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return res;
}

Matrix power(Matrix a, int k) {
    Matrix res = I;
    while (k) {
        if (k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

const int MN = 22;
int m, n, q, id[MN][MN];

const int di[5] = {-1,1,0,0,0};
const int dj[5] = {0,0,-1,1,0};

bool outside(int u, int v) {
    return u < 1 || v < 1 || u > m || v > n;
}

void init() {
    int cur = 0;
    FOR(i,1,m) FOR(j,1,n) id[i][j] = cur++;

    memset(I.x, 0, sizeof I.x);
    memset(A.x, 0, sizeof A.x);

    sz = m * n;
    REP(i,sz) I.x[i][i] = 1;

    FOR(i,1,m) FOR(j,1,n) {
        REP(dir,5) {
            int ii = i + di[dir], jj = j + dj[dir];
            if (outside(ii, jj)) continue;

            A.x[ id[i][j] ][ id[ii][jj] ] = 1;
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> q) {
        init();

        memset(f.x, 0, sizeof f.x);
        f.x[0] = 1;

        int cur_time = 1;

        while (q--) {
            int typ; cin >> typ;
            int x, y, t; cin >> x >> y >> t;

            // update until time moment t-1
            Matrix up = power(A, t - 1 - cur_time);
            f = update(f, up);

            if (typ == 2) {
                // cannot go to cell (x, y)
                REP(dir,5) {
                    int xx = x + di[dir], yy = y + dj[dir];
                    if (outside(xx, yy)) continue;

                    A.x[ id[x][y] ][ id[xx][yy] ] = 0;
                }
            }
            f = update(f, A);

            if (typ == 1) {
                cout << (int) f.x[id[x][y]] << '\n';
            }
            cur_time = t;

            if (typ == 3) {
                // can now go to cell (x, y)
                REP(dir,5) {
                    int xx = x + di[dir], yy = y + dj[dir];
                    if (outside(xx, yy)) continue;

                    A.x[ id[x][y] ][ id[xx][yy] ] = 1;
                }
            }
        }
    }
}
