// f(u) = số tplt nếu chọn u và 1 số đỉnh trong T(u)
// f(u) = product( f(v) + 1 )
//
// -> O(N)
//
// for S:
//    -> f(u) = số tplt nếu không chọn các mặt hàng trong S
//            = số tplt nếu có thể chọn trong (2^k-1 - S)
//
// cnt( đủ 1 -> k )
// = cnt( 2^k-1 )
// - cnt( 2^k-1 - 2^x )
// + cnt( 2^k-1 - 2^x - 2^y)

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

const int MOD = (int) 1e9 + 7;
int n, k;

int contains(int mask, int i) {
    if (i > 20) return 0;
    return (mask>>i) & 1;
}

void dfs(int u, int father,
        const vector<vector<int>>& adj,
        const vector<int>& c,
        const int cannot,
        vector<int>& f) {

    if (contains(cannot, c[u])) {
        f[u] = 0;
    } else {
        f[u] = 1;
    }

    for (int v : adj[u]) {
        if (v == father) {
            continue;
        }

        dfs(v, u, adj, c, cannot, f);

        int cnt_v = (1 + f[v]) % MOD;
        f[u] = (f[u] * cnt_v) % MOD;
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    // input
    while (cin >> n >> k) {
        vector<int> c(n);
        for (int& x : c) {
            cin >> x;
            --x;
        }

        vector<vector<int>> adj(n);
        for (int i = 0; i < n-1; i++) {
            int u, v; cin >> u >> v;
            --u; --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int res = 0;
        for (int cannot = 0; cannot < TWO(k); cannot++) {
            vector<int> f(n, 0);
            dfs(0, -1, adj, c, cannot, f);

            int sum = std::accumulate(f.begin(), f.end(), 0LL) % MOD;

            if (__builtin_popcount(cannot) % 2 == 0) {
                res = (res + sum) % MOD;
            } else {
                res = (res - sum + MOD) % MOD;
            }
        }
        cout << res << endl;
        break;
    }
    return 0;
}
