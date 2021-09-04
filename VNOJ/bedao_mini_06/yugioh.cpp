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

const int MV = 1e6;
int sieve[MV + 11];

int X, n;

bool isGood(int val) {
    if (val > X) return false;
    if (val <= 0) return false;

    return sieve[val] == 0;
}

int good[MV + 11];

int32_t main() {
    ios::sync_with_stdio(0);

    for (int i = 2; i <= 1000; i++) {
        if (!sieve[i]) {
            for (int j = i*i; j <= MV; j += i) {
                sieve[j] = i;
            }
        }
    }
    sieve[1] = 1;

    cin >> n >> X;
    vector<int> goodPos;

    int nGood = 0;
    for (int i = 0; i < n; i++) {
        int val; cin >> val;
        if (isGood(val)) {
            good[i] = 1;
            ++nGood;
        }
    }
    for (int i = 1; i < n; i++) {
        good[i] = good[i-1] + good[i];
    }
    // good[i] = so vi tri tot tu 0 -> i

    int res = nGood;
    for (int left = 0, right = nGood - 1; right < n; left++, right++) {
        int cur = good[right];
        if (left) cur -= good[left - 1];

        res = min(res, nGood - cur);
    }
    cout << res << endl;
    return 0;
}
