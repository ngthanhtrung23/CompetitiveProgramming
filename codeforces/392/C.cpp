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

const int MN = 88;
const int MOD = 1000000007;

int p2[MN], c[MN][MN];

int mul(int a, int b) {
    return a * (long long) b % MOD;
}
int add(int a, int b) {
    return (a + b) % MOD;
}

void init() {
    p2[0] = 1;
    FOR(i,1,80) p2[i] = mul(p2[i-1], 2);
    FOR(i,0,80) {
        c[i][0] = 1;
        FOR(j,1,i)
            c[i][j] = add(c[i-1][j-1], c[i-1][j]);
    }
}

int power(int x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    int mid = power(x, k >> 1);
    mid = mul(mid, mid);
    if (k & 1) return mul(mid, x);
    else return mid;
}

int sz;
struct Matrix {
    int x[88][88];

    void print() {
        REP(i,sz) {
            REP(j,sz) cout << x[i][j] << ' ';
            cout << endl;
        }
    }
} I, p[88];
int start[88];

Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c;
    REP(i,sz) REP(j,sz) {
        c.x[i][j] = 0;
        REP(k,sz)
            c.x[i][j] = add(c.x[i][j], mul(a.x[i][k], b.x[k][j]));
    }
    return c;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    init();
    long long n;
    int k;
    while (cin >> n >> k) {
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        sz = 2*k + 3;
        memset(I.x, 0, sizeof I.x);
        REP(i,sz) I.x[i][i] = 1;

        memset(p[0].x, 0, sizeof p[0].x);
        p[0].x[0][0] = 1;
        FOR(i,1,k+1) {
            p[0].x[i][i+k+1] = 1;
        }
        FOR(x,0,k) {
            FOR(y,0,x) {
                p[0].x[x+k+2][y+k+2] = c[x][y];
                p[0].x[x+k+2][y+1] = mul(c[x][y], p2[x-y]);
            }
        }
        FOR(j,1,2*k+2) p[0].x[0][j] = p[0].x[sz-1][j];
//        p[0].print();

        FOR(i,1,64) p[i] = p[i-1] * p[i-1];

        start[0] = add(1, mul(2, power(2, k)));
        start[1] = 1;
        FOR(i,2,k+1) start[i] = mul(start[i-1], 1);
        start[k+2] = 2;
        FOR(i,k+3,sz-1) start[i] = mul(start[i-1], 2);

//        PR0(start, sz);
        Matrix res = I;
        n -= 2;
        FOR(bit,0,62)
            if (n & (1LL<<bit)) {
                res = res * p[bit];
            }

        int sum = 0;
        REP(i,sz)
            sum = add(sum, mul(res.x[0][i], start[i]));
        cout << sum << endl;
    }
    return 0;
}
