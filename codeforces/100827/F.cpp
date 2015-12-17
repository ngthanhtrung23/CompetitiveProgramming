
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const ll MOD = 1e9 + 9;

int sz;
struct Matrix {
    int x[88][88];
} I, trans;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    REP(i,sz) REP(j,sz) {
        res.x[i][j] = 0;
        REP(k,sz)
            res.x[i][j] = (res.x[i][j] + a.x[i][k] * (ll) b.x[k][j]) % MOD;
    }
    return res;
}

Matrix power(Matrix a, int k) {
    Matrix res = I;
    while (k > 0) {
        if (k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

bool check(int m, int n, int a[][4]) {
    REP(i,m) REP(j,n) if (a[i][j])
        FOR(u,i,m-1) REP(v,n) if (a[u][v]) {
            if (sqr(i-u) + sqr(j-v) == 5) return false;
        }
    return true;
}

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))
int id[666];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int m, n; cin >> m >> n;
        if (n == 1) {
            cout << (1<<m) << endl;
            continue;
        }
        int a[3][4];
        sz = 0;
        memset(id, -1, sizeof id);
        REP(mask,TWO(m+m)) {
            int cur = 0;
            REP(i,2) REP(j,m) {
                if (CONTAIN(mask,cur)) a[i][j] = 1;
                else a[i][j] = 0;
                ++cur;
            }
            if (check(2, m, a)) {
                id[mask] = sz;
                ++sz;
            }
        }
        REP(i,sz) I.x[i][i] = 1;

        memset(trans.x, 0, sizeof trans.x);
        REP(mask,TWO(m+m+m)) {
            int cur = 0;
            REP(i,3) REP(j,m) {
                if (CONTAIN(mask,cur)) a[i][j] = 1;
                else a[i][j] = 0;
                ++cur;
            }
            if (check(3, m, a)) {
                int cur = 0;

                int u = 0;
                FOR(i,0,1) REP(j,m) {
                    u += a[i][j] << cur;
                    cur++;
                }
                cur = 0;
                int v = 0;
                FOR(i,1,2) REP(j,m) {
                    v += a[i][j] << cur;
                    cur++;
                }

                trans.x[id[v]][id[u]]++;
            }
        }
        trans = power(trans, n - 2);
        ll res = 0;
        REP(i,sz) REP(j,sz) res = (res + trans.x[i][j]) % MOD;
        cout << res << endl;
    }
}
