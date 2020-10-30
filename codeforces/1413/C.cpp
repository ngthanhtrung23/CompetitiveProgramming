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

struct Counter {
    unordered_map<int, int> cnt;
    int unique;

    Counter() : unique(0) {}

    void add(int val) {
        cnt[val]++;
        if (cnt[val] == 1) ++unique;
    }

    void remove(int val) {
        assert(cnt[val] > 0);
        cnt[val]--;
        if (cnt[val] == 0) --unique;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    vector<int> a(6);
    REP(i,6) cin >> a[i];

    int n; cin >> n;
    vector< pair<int,int> > all;
    REP(i,n) {
        int val; cin >> val;
        REP(j,6) {
            all.push_back({val - a[j], i});
        }
    }
    sort(ALL(all));

    Counter cnt;
    int right = -1;
    int res = 1000111000111LL;
    for (int left = 0; left < SZ(all); left++) {
        while (right + 1 < SZ(all) && cnt.unique < n) {
            right++;
            cnt.add(all[right].second);
        }
        if (cnt.unique == n) {
            res = min(res, all[right].first - all[left].first);
        }
        cnt.remove(all[left].second);
    }
    cout << res << endl;

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
