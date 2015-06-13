
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

unsigned long long n, k, l, m;

struct Matrix {
    unsigned long long x[2][2];
} T, trans[70], I;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    REP(i,2) REP(j,2) {
        res.x[i][j] = 0;
        REP(k,2)
            res.x[i][j] = (res.x[i][j] + a.x[i][k] * b.x[k][j]) % m;
    }
    return res;
}

unsigned long long fibo(unsigned long long n) {
    ++n;
    Matrix all = I;
    REP(i,63)
        if ((n >> (unsigned long long) i) & 1LL) {
            all = all * trans[i];
        }
    return (all.x[0][0] + all.x[0][1]) % m;
}

unsigned long long power(unsigned long long x, unsigned long long n) {
    if (n == 0) return 1 % m;
    if (n == 1) return x % m;
    unsigned long long mid = power(x * x % m, n >> 1);
    if (n & 1) return mid * x % m;
    else return mid;
}

int main() {
    ios :: sync_with_stdio(false);
    T.x[0][0] = 0; T.x[0][1] = 1;
    T.x[1][0] = 1; T.x[1][1] = 1;

    I.x[0][0] = I.x[1][1] = 1;

    while (cin >> n >> k >> l >> m) {
        trans[0] = T;
        FOR(i,1,69) trans[i] = trans[i-1] * trans[i-1];
    
        if (l == 0) {
            if (k == 0) cout << 1 % m << endl;
            else cout << 0 << endl;
            continue;
        }
        if (l < 64 && (1LL<<l) <= k) {
            cout << 0 << endl;
            continue;
        }
        unsigned long long p2 = power(2, n);

        unsigned long long res = 1;
        unsigned long long fibon = fibo(n);
        REP(bit,l) {
            int need = (k >> (unsigned long long) bit) & 1;

            if (need == 0) {
                res = res * fibon % m;
            }
            else {
                res = res * (p2 - fibon + m) % m;
            }
        }
        cout << res % m << endl;
    }
    return 0;
}
