
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

struct Matrix {
    long long x[2][2];
} I, A, p;
long long m, l, r, k;

Matrix operator * (const Matrix &a, const Matrix &b) {
    static Matrix c;
    memset(c.x, 0, sizeof c.x);
    REP(i,2) REP(j,2) {
        REP(k,2)
            c.x[i][j] = (c.x[i][j] + a.x[i][k] * b.x[k][j]) % m;
    }
    return c;
}

Matrix power(long long k) {
    if (k == 0) return I;
    if (k == 1) return A;
    Matrix mid = power(k >> 1);
    mid = mid * mid;
    if (k & 1) return mid * A;
    else return mid;
}

ll get(ll l, ll r, ll x) {
    return (r - r % x) / x - (l-1 - (l-1) % x) / x;
}

int main() {
    I.x[0][0] = I.x[1][1] = 1;
    A.x[0][1] = A.x[1][0] = A.x[1][1] = 1;
    while (cin >> m >> l >> r >> k) {
        ll res = 0;
        FOR(i,1,1000111) if (get(l, r, i) >= k) res = i;
        ll len = r - l + 1;
        ll bound = len / (k-1);
        FOR(i,bound-1000111,bound)
            if (i > 0)
            if (get(l, r, i) >= k) res = max(res, (ll) i);

        ll d = (r - l) / (k - 1);
        while (d > 1) {
            if (get(l, r, d) >= k) {
                res = max(res, d);
                break;
            }
            ll n = 1 + r / d;
            d -= ( ((n*d) - r) + (n-1) ) / n;
        }


        p = power(res);
        cout << p.x[0][1] % m << endl;
    }
    return 0;
}
