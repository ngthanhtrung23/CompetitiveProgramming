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

int solve(const vector<int>& res) {
    set<int> diffs;
    for (int i = 1; i < SZ(res); i++) {
        diffs.insert(res[i] - res[i-1]);
    }
    return SZ(diffs);
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n, k;
    while (cin >> n >> k) {
        int left = 1, right = n;
        vector<int> res;
        REP(turn,k) {
            if (turn % 2 == 0) {
                res.push_back(left++);
            } else {
                res.push_back(right--);
            }
        }
        if (k % 2 == 1) {
            FOR(i,left,right)
                res.push_back(i);
        } else {
            FORD(i,right,left)
                res.push_back(i);
        }
        assert(solve(res) == k);
        for (int x : res) cout << x << ' '; cout << endl;
    }
    return 0;
}
