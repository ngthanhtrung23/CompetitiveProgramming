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

const int INF = 1000111000;
int res[1011];

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;

        set<int> all(a.begin(), a.end());
        map<int, vector<int>> ids;

        for (int val : all) {
            ids[val].push_back(-1);
        }

        for (int i = 0; i < n; i++) {
            ids[a[i]].push_back(i);
        }

        for (int val : all) {
            ids[val].push_back(n);
        }

        FOR(i,1,n) res[i] = INF;

        for (int val : all) {
            int max_dist = -1;
            for (int i = 1; i < SZ(ids[val]); i++) {
                max_dist = max(max_dist, ids[val][i] - ids[val][i-1]);
            }
            FOR(i,max_dist,n) {
                res[i] = min(res[i], val);
            }
        }

        FOR(i,1,n) {
            cout << ((res[i] == INF) ? -1 : res[i]) << ' ';
        }
        cout << '\n';
    }
    return 0;
}
