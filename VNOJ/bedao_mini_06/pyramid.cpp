// a, b, c
// a^2 + b^2 = c^2
//
// c - a OR c - b = X
// a + b = Y
//
//
// c - a = X
// c = (X + a)
// b = Y - a
//
// a^2 + (Y - a)^2 = (X + a)^2
// a^2 + (a - Y)^2 - (a + X)^2 = 0
//
// a^2 + a^2 - 2aY + Y^2 - a^2 - 2aX - X^2 = 0
// a^2 - 2*(X+Y)*a + Y^2 - X^2

#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

int32_t main() {
    ios::sync_with_stdio(0);
    long double x, y; cin >> x >> y;
    /*
    FOR(a,1,y-1) {
        int b = y - a;
        int cc = a*a + b*b;
        int c = (int) sqrt(cc + 0.5);
        if (c*c != cc) continue;

        if (c - a == x || c - b == x) {
            cout << a << ' ' << b << ' ' << c << endl;
            return 0;
        }
    }
    */

    long double A = 1;
    long double B = -2 * (x + y);
    long double C = -x*x + y*y;
    long double delta = B*B - 4*A*C;
    assert(delta >= 0);

    long double a = (-B + sqrt(delta)) / 2.0 / A;
    long double b = y - a;
    if (b < 0 || b > y) {
        a = (-B - sqrt(delta)) / 2.0 / A;
        b = y - a;
    }
    long double c = sqrt(a*a + b*b);
    cout << (fixed) << setprecision(9);
    if (a > b) swap(a, b);
    cout << a << ' ' << b << ' ' << c << endl;
    return 0;
}
