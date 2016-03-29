
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MOD = 1e9 + 9;

int k, d, m;

struct Matrix {
    int x[4][4];

    void print() {
        REP(i,4) {
            REP(j,4) cout << x[i][j] << ' ';
            cout << endl;
        }
        cout << endl;
    }
} I, trans;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    REP(i,4) REP(j,4) {
        res.x[i][j] = 0;
        REP(k,4) res.x[i][j] = (res.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return res;
}

Matrix power(const Matrix& a, int k) {
    if (k == 0) return I;
    if (k == 1) return a;
    auto mid = power(a, k >> 1);
    mid = mid * mid;

    if (k & 1) return mid * a;
    return mid;
}

int solve(int x, int y, int k) {
    int c = y - x + 1;
    if (c < 1) return 0;
    if (c == 1) return 1;

    memset(I.x, 0, sizeof I.x);
    REP(i,4) I.x[i][i] = 1;

    memset(trans.x, 0, sizeof trans.x);

    trans.x[0][0] = c - 2;
    trans.x[1][0] = trans.x[2][0] = trans.x[3][1] = trans.x[3][2] = 1;
    trans.x[1][1] = trans.x[2][2] = c - 1;
    trans.x[3][3] = c;

    trans = power(trans, k);

    return trans.x[3][0];
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> k) {
        cin >> d >> m;
        if (m % d) {
            cout << 0 << endl;
            continue;
        }
        int res = 1;
        for(int i = 2; i * i <= m; ++i)
            if (m % i == 0) {
                int p = i, y = 0, x = 0;
                while (m % p == 0) {
                    ++y;
                    m /= p;
                }

                while (d % p == 0) {
                    ++x;
                    d /= p;
                }
                res = res * solve(x, y, k) % MOD;
            }
        if (m > 1) {
            int p = m, y = 0, x = 0;
            while (m % p == 0) ++y, m /= p;
            while (d % p == 0) ++x, d /= p;

            res = res * solve(x, y, k) % MOD;
        }
        assert(m == 1);
        assert(d == 1);

        cout << res << endl;
    }
}
