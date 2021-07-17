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

const int MOD = 1e9 + 7;
int bit[2011];

int get(int u) {
    int res = 0;
    for (int x = u; x > 0; x -= x & -x) {
        res = (res + bit[x]) % MOD;
    }
    return res;
}

void update(int u, int val) {
    for (int x = u; x < 2011; x += x & -x) {
        bit[x] = (bit[x] + val) % MOD;
    }
}

int32_t main() {
    ios::sync_with_stdio(0);

    // read input
    int n; cin >> n;
    vector< pair<int,int> > a(n);
    for (auto& p : a) cin >> p.first;
    for (auto& p : a) cin >> p.second;
    sort(a.begin(), a.end());

    // RR a.second
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = a[i].second;
    }
    sort(c.begin(), c.end());
    c.resize(unique(c.begin(), c.end()) - c.begin());
    for (int i = 0; i < n; i++) {
        a[i].second = lower_bound(c.begin(), c.end(), a[i].second) - c.begin() + 1;
    }

    vector<vector<int>> f(n+1, vector<int> (n+1, 0));
    // length = 1
    for (int i = 0; i < n; i++) {
        f[1][i] = 1;
    }

    for (int len = 2; len <= n; len++) {
        memset(bit, 0, sizeof bit);
        for (int i = 0; i < n; i++) {
            f[len][i] = get(n - a[i].second);
            update(n+1-a[i].second, f[len-1][i]);
        }
    }

    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 0; j < SZ(f[i]); j++) {
            sum = (sum + f[i][j]) % MOD;
        }
        cout << sum << ' ';
    }
    cout << endl;
    return 0;
}
