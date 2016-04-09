
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

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MOD = 1e9 + 7;
const int INF = 1000111000111000111LL;

struct Elem {
    int len, cnt;

    Elem() {}
    Elem(int len, int cnt) : len(len), cnt(cnt) {}
};

Elem operator * (const Elem& a, const Elem& b) {
    Elem res;
    res.len = a.len + b.len;
    res.cnt = a.cnt * b.cnt % MOD;
    return res;
}
Elem operator + (const Elem& a, const Elem& b) {
    Elem res = a;
    if (b.len < res.len) res = b;
    else if (b.len == res.len) {
        res.cnt = (res.cnt + b.cnt) % MOD;
    }
    return res;
}

struct Matrix {
    Elem x[155][155];
} c, I, res;
int n, m, k;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    REP(i,n) REP(j,n) res.x[i][j] = Elem(INF, 0);

    REP(i,n) REP(j,n) REP(k,n)
        res.x[i][j] = res.x[i][j] + (a.x[i][k] * b.x[k][j]);
    return res;
}

Matrix power(Matrix x, int k) {
    Matrix res = I;
    while (k > 0) {
        if (k & 1) res = res * x;
        x = x * x;
        k >>= 1;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        GI(m); GI(k);

        REP(i,n) REP(j,n) {
            if (i == j) {
                I.x[i][j] = Elem(0, 1);
            } else {
                I.x[i][j] = Elem(INF, 0);
            }
            c.x[i][j] = Elem(INF, 0);
        }

        while (m--) {
            int u, v, len;
            GI(u); GI(v); GI(len);
            --u; --v;

            c.x[u][v] = c.x[u][v] + Elem(len, 1);
            c.x[v][u] = c.x[u][v];
        }
        res = power(c, k);
        REP(i,n) {
            REP(j,n) {
                if (res.x[i][j].len == INF) printf("X ");
                else printf("%lld ", res.x[i][j].len);
                printf("%lld ", res.x[i][j].cnt);
            }
            puts("");
        }
    }
}
