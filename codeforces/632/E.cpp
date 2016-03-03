
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << X << endl; }
#define PR(A,n)  { cerr << #A << " = "; FOR(_,1,n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A,n) { cerr << #A << " = "; REP(_,n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int my_round(double x) {
    if (x < 0) return -my_round(-x);
    return (int) (x + 1e-3);
}

const double PI = acos((double) -1.0);

typedef complex<double> cplex;
const int MN = 3000111;
int rev[MN];
cplex wlen_pw[MN], fa[MN], fb[MN];

void fft(cplex a[], int n, bool invert) {
    for (int i = 0; i < n; ++i) if (i < rev[i]) swap (a[i], a[rev[i]]);

    for (int len = 2; len <= n; len <<= 1) {
        double alpha = 2 * PI / len * (invert ? -1 : +1);
        int len2 = len >> 1;

        wlen_pw[0] = cplex(1, 0);
        cplex wlen(cos(alpha), sin(alpha));
        for (int i = 1; i < len2; ++i) wlen_pw[i] = wlen_pw[i-1] * wlen;

        for (int i = 0; i < n; i += len) {
            cplex t, *pu = a+i, *pv = a + i + len2,
                    *pu_end = a + i + len2, *pw = wlen_pw;
            for (; pu != pu_end; ++pu, ++pv, ++pw) {
                t = *pv * *pw;
                *pv = *pu - t;
                *pu += t;
            }
        }
    }

    if (invert) REP(i, n) a[i] /= n;
}

void calcRev(int n, int logn) {
    REP(i, n) {
        rev[i] = 0;
        REP(j, logn) if (i & (1 << j)) rev[i] |= 1 << (logn - 1 - j);
    }
}

void mulpoly(ll a[], ll b[], ll c[], int na, int nb, int &n) {
    int l = max(na, nb), logn = 0;
    for (n = 1; n < l; n <<= 1) ++logn;
    n <<= 1; ++logn;
    calcRev(n, logn);

    REP(i,n) fa[i] = fb[i] = cplex(0);
    REP(i,na) fa[i] = cplex(a[i]);
    REP(i,nb) fb[i] = cplex(b[i]);

    fft(fa, n, false);
    fft(fb, n, false);

    REP(i,n) fa[i] *= fb[i];
    fft(fa, n, true);

    REP(i,n) {
        c[i] = (ll)(fa[i].real() + 0.5);
        if (c[i]) c[i] = 1;
    }
}

int k, n[11];
ll f[10][MN], res[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int q;
    while (cin >> q >> k) {
        memset(f, 0, sizeof f);
        memset(res, 0, sizeof res);
        FOR(i,1,q) {
            int x; cin >> x;
            f[0][x] = 1;
        }
        n[0] = 1005;
        FOR(i,1,9) {
            mulpoly(f[i-1], f[i-1], f[i], n[i-1], n[i-1], n[i]);
        }
        FOR(i,1,1000) res[i] = f[0][i];

        int nres = 1005;
        --k;
        FOR(i,0,9) {
            if ((k >> i) & 1) {
                mulpoly(res, f[i], res, nres, n[i], nres);
            }
        }
        FOR(i,0,nres) if (res[i]) cout << i << ' '; cout << endl;
    }
}
