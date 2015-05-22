
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

bool can[55][55];

int getId(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    else return c - 'A' + 26;
}

long long n;
int m, k;

const long long MOD = 1e9 + 7;
struct Matrix {
    int m, n;
    long long x[55][55];

    void print() {
        cout << "m = " << m << ", n = " << n << endl;
        REP(i,m) {
            REP(j,n) cout << x[i][j] << ' ';
            cout << endl;
        }
    }
} trans[66], start, target, T;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix c;
    c.m = a.m; c.n = b.n;

    REP(i,c.m) REP(j,c.n) {
        c.x[i][j] = 0;
        REP(k,a.n)
            c.x[i][j] = (c.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return c;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> k) {
        memset(can, true, sizeof can);
        FOR(i,1,k) {
            string s; cin >> s;
            int u = getId(s[0]);
            int v = getId(s[1]);

            can[u][v] = false;
        }
        memset(trans[0].x, 0, sizeof trans[0].x);
        trans[0].m = trans[0].n = m;

        REP(to,m) REP(from,m)
            if (can[from][to])
                trans[0].x[to][from] = 1;
        FOR(i,1,62) trans[i] = trans[i-1] * trans[i-1];

//        trans[0].print();

        start.m = m; start.n = 1;
        REP(i,m) start.x[i][0] = 1;

        Matrix T; T.m = T.n = m;
        REP(i,m) REP(j,m) T.x[i][j] = (i == j) ? 1 : 0;

        --n;
        REP(t,63)
            if ((n >> t) & 1) {
                T = T * trans[t];
            }
        target = T * start;
        long long res = 0;
        REP(i,m)
            res = (res + target.x[i][0]) % MOD;

        cout << res << endl;
    }
    return 0;
}

