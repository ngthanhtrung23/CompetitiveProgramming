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

const long long MOD = 1000000007LL;
long long fib[111], trib[111], ff[22];

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % MOD;
    long long mid = power(x, k >> 1);
    mid = mid * mid % MOD;

    if (k & 1) return mid * x % MOD;
    else return mid;
}

void init() {
    fib[0] = 0;
    fib[1] = 1;
    FOR(i,2,100) fib[i] = (fib[i-1] + fib[i-2]) % MOD;

    trib[0] = 0;
    trib[1] = trib[2] = 1;
    FOR(i,3,100) trib[i] = (trib[i-1] + trib[i-2] + trib[i-3]) % (MOD - 1LL);

    FOR(i,1,10) ff[i] = power(fib[i+25], trib[i+20]);
}

struct Matrix {
    int m, n;
    long long x[11][11];
} I, p[44], start;

Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c;
    memset(c.x, 0, sizeof c.x);
    c.m = a.m; c.n = b.n;
    REP(i,c.m) REP(j,c.n) {
        REP(k,a.n)
            c.x[i][j] = (c.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return c;
}

long long a[111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    init();
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        FOR(i,0,9) cin >> a[i];
        int x; cin >> x;
        cout << "Case #" << test << ": ";
        if (x < 10) cout << a[x] << endl;
        else {
            I.m = I.n = 10;
            REP(i,10) I.x[i][i] = 1;
            
            start.m = 10; start.n = 1;
            REP(i,10) start.x[i][0] = a[i];
            
            p[0].m = p[0].n = 10;
            REP(i,9) p[0].x[i][i+1] = 1;
            long long sum = 0;
            REP(j,10) {
                sum = (sum + ff[10-j]) % MOD;
                p[0].x[9][j] = sum;
            }
            FOR(i,1,40) p[i] = p[i-1] * p[i-1];

            Matrix res = I;
            x = x - 9;
            FOR(bit,0,35)
                if ((1LL<<bit) & x) {
                    res = res * p[bit];
                }

            Matrix target = res * start;
            cout << target.x[9][0] << endl;
        }
    }
    return 0;
}
