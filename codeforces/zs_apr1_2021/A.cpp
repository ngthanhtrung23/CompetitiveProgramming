// trick: pacman can go through top/bottom/left/right borders

#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
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
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

double f[22];

int32_t main() {
    ios::sync_with_stdio(0);
    f[21] = 21.0;
    FORD(i,20,1) {
        double stay = i;
        double go = 0.0;

        FOR(val,1,13) {
            int next = i + val;

            // A can be used as 1 or 14
            if (val == 1 && i + 14 <= 21) next = i + 14;

            double f_next = (next > 21) ? 0 : f[next];
            go += 1.0 / 13 * f_next;
        }

        f[i] = max(stay, go);
    }
    FOR(i,1,21) cout << i << ' ' << f[i] << endl;
    return 0;
}
