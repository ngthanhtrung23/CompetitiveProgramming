#include <bits/stdc++.h>
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

const int MN = 300111;

int f[50111][5][5];
int my_round(double x) {
    if (x < 0) return -my_round(-x);
    return (int) (x + 1e-3);
}

const double PI = acos((double) -1.0);

typedef complex<double> cplex;
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

    REP(i,n) c[i] = (ll)(fa[i].real() + 0.5);
}

ll x[MN], y[MN], z[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    string a, b;
    while (cin >> a >> b) {
        int n = SZ(a);
        FOR(ca,'A','E') FOR(cb,'a','e') {
            REP(i,n) x[i] = a[i] == ca;
            REP(i,n) y[i] = b[n-i-1] == cb;

            int nc = 0;
            mulpoly(x, y, z, n, n, nc);

            REP(rot,n) {
                f[rot][ca - 'A'][cb - 'a'] = z[n - rot - 1] + z[n - rot - 1 + n];
//                cout << f[rot][ca - 'A'][cb - 'a'] << ' ';
            }
//            cout << endl;
        }
        int res = 0;
        REP(rot,n) {
            int t[5];
            REP(i,5) t[i] = i;
            do {
                int cur = 0;
                REP(i,5) cur += f[rot][i][t[i]];
                res = max(res, cur);
            } while (next_permutation(t, t+5));
        }
        cout << n - res << endl;
    }
}
