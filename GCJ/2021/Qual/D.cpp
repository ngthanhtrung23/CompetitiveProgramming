// Algo:
// - Using 1 query, we can find order of first three elements: x1 < x2 < x3
//   (we can assume x1 < x2)
// - For each i from 4 to N:
//   - Use binary search to find position of xi
//   - Can also use ternary search, but it's not necessary to get AC

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

mt19937 rng(777666555);
#define random_shuffle askcjaljc

const bool DEBUGGING = false;

vector<int> correct;
int cnt_query = 0;
int med(int x, int y, int z) {
    cout << x << ' ' << y << ' ' << z << endl;
    ++cnt_query;

    if (DEBUGGING) {
        int cnt = 0;
        for (int val : correct) {
            if (val == x || val == y || val == z) {
                ++cnt;
                if (cnt == 2) {
                    cout << "DEBUG --> " << val << endl;
                    return val;
                }
            }
        }
        assert(false);
    }

    int res; cin >> res;
    return res;
}

void gen_correct(int n) {
    correct.resize(n);
    std::iota(correct.begin(), correct.end(), 1);
    shuffle(correct.begin(), correct.end(), rng);
}

int32_t main() {
    ios::sync_with_stdio(0);
    int t, n, q; cin >> t >> n >> q;
    assert(n >= 3);

    while (t--) {
        if (DEBUGGING) {
            gen_correct(n);
            PR0(correct, n);
        }

        vector<int> ids(n);
        std::iota(ids.begin(), ids.end(), 1);
        shuffle(ids.begin(), ids.end(), rng);
        // PR0(ids, n);

        int m = med(ids[0], ids[1], ids[2]);
        vector<int> sorted {ids[0], ids[1], ids[2]};
        if (ids[0] == m) swap(sorted[0], sorted[1]);
        else if (ids[2] == m) swap(sorted[2], sorted[1]);

        // PR0(sorted, SZ(sorted));

        FOR(i,3,n-1) {
            // where should we put ids[i]
            
            int l = 0, r = SZ(sorted), res = -1;
            while (l < r) {
                int mid = (l + r) / 2;
                if (mid > 0) --mid;

                int cur = med(sorted[mid], sorted[mid+1], ids[i]);
                if (cur == ids[i]) {
                    res = mid + 1;
                    break;
                } else if (cur == sorted[mid]) {
                    res = mid;
                    r = mid;
                } else {
                    l = mid + 2;
                    res = mid + 2;
                }
            }

            assert(res >= 0 && res <= SZ(sorted));
            sorted.insert(sorted.begin() + res, ids[i]);

            // PR0(sorted, SZ(sorted));
        }

        vector<int> rev = correct;
        reverse(rev.begin(), rev.end());

        // PR0(rev.begin(), SZ(rev));
        if (DEBUGGING) assert(sorted == correct || sorted == rev);

        for (int val : sorted) cout << val << ' '; cout << endl;
        int AC; if (!DEBUGGING) { cin >> AC; assert(AC == 1); }
    }
    if (DEBUGGING) {
        DEBUG(cnt_query);
    }

    return 0;
}

