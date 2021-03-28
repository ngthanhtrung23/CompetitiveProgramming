// Algo:
// - can(n, sum) = can we construct array with n elements and cost = sum?
// - solve(n) = recursively construct array for n
//   - loop through all positions of 1
//   - use can(n-1, sum-...) to check whether we can construct the rest

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

bool can(int n, int sum) {
    return n - 1 <= sum && sum <= n * (n+1) / 2 - 1;
}

vector<int> solve(int n, int sum) {
    assert(can(n, sum));
    
    if (n == 1) {
        assert(sum == 0);
        return {1};
    }

    REP(pos,n) {
        if (can(n-1, sum - pos - 1)) {
            auto res = solve(n - 1, sum - pos - 1);

            REP(i,SZ(res)) res[i] += 1;
            res.insert(res.begin(), 1);

            reverse(res.begin(), res.begin() + pos + 1);
            return res;
        }
    }

    // unreachable
    assert(false);
    return {};
}

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n, sum; cin >> n >> sum;

        if (!can(n, sum)) {
            cout << "Case #" << test << ": IMPOSSIBLE" << endl;
            continue;
        }

        vector<int> res = solve(n, sum);
        cout << "Case #" << test << ":";
        for (int x : res) cout << ' ' << x;
        cout << endl;
    }
    return 0;
}

