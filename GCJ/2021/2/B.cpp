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
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int MN = 1000000;
int ln[MN + 11];

void go(int start, int sum, int cnt) {
    ln[sum] = max(ln[sum], cnt);
    for (int next = start * 2; sum + next < MN / 3; next += start) {
        go(next, sum + next, cnt + 1);
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    FOR(start,1,MN / 3) {
        go(start, start, 1);
    }
    // FOR(i,1,MN / 3) cout << i << ' ' << ln[i] << endl;

    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n; cin >> n;
        int res = 1;
        for (int start = 3; start*start <= n; start++) {
            if (n % start) continue;

            res = max(res, ln[n / start]);
            res = max(res, ln[start]);
        }
        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}
