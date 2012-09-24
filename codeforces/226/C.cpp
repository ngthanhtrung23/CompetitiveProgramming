#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const long double PI = acos((long double) -1.0);

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

long long get(long long t) {
    static long long ll, rr;
    rr = r - r % t;
    ll = l - l % t; if (ll < l) ll += t;
    if (ll > rr) return 0;
    else return (rr/t - ll/t) + 1;
}

int main() {
    cin >> m >> l >> r >> k;
    I.x[0][0] = I.x[1][1] = 1;
    A.x[0][1] = A.x[1][0] = A.x[1][1] = 1;
    long long res = 0;
    for(long long t = 1; t*t <= r; ++t) {
        if (get(t) >= k) res = max(res, t);
        if (get(r/t) >= k) res = max(res, r/t);
    }
    p = power(res);
    cout << p.x[0][1] % m << endl;
    return 0;
}
