
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

const ll MOD = 1e9 + 7;
int sz;
struct Matrix {
    ll x[111][111];
} trans;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    REP(i,sz) REP(j,sz) {
        res.x[i][j] = 0;
        REP(k,sz) res.x[i][j] = (res.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return res;
}
Matrix power(Matrix a, int k) {
    Matrix res;
    memset(res.x, 0, sizeof res.x);
    REP(i,sz) res.x[i][i] = 1;

    while (k > 0) {
        if (k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }

    return res;
}

int cnt[11];
int n, b, k, x;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> b >> k >> x) {
        memset(cnt, 0, sizeof cnt);
        while (n--) {
            int a; cin >> a;
            cnt[a] ++;
        }
        memset(trans.x, 0, sizeof trans.x);
        sz = x;
        REP(fr,x) {
            REP(add,10) {
                int to = (fr * 10 + add) % x;
                trans.x[to][fr] += cnt[add];
            }
        }
        trans = power(trans, b);
        cout << trans.x[k][0] << endl;
    }
}
