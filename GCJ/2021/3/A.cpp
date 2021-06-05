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

// a: minimum possible, b: maximum possible
int construct(vector<int> digits, int a, int b) {
    sort(ALL(digits));
    assert(SZ(digits) % 2 == 0);
    for (int i = 0, j = SZ(digits) - 1; i < j; i++, j--) {
        a = a * 10 + digits[i];
        b = b * 10 + digits[j];
    }
    return llabs(a - b);
}

int solve(vector<int> digits) {
    // odd number of digits -> greedy
    if (SZ(digits) % 2) {
        REP(i,SZ(digits)) if (digits[i]) {
            vector<int> ds = digits;
            ds.erase(ds.begin() + i);

            return construct(ds, digits[i], 0);
        }
        return -1;
    }

    vector<int> pairs;  // pairs of digits
    vector<int> remainings;  // non-pairs
    map<int,int> cnt;
    for (int d : digits) cnt[d]++;

    for (auto [d, c] : cnt) {
        if (c >= 2) {
            REP(turn,c/2) pairs.push_back(d);
            c %= 2;
        }
        if (c) remainings.push_back(d);
    }
    if (remainings.empty()) return 0;

    int res = LLONG_MAX;
    REP(mask,TWO(SZ(pairs))) {  // brute force common prefix
        vector<int> ds = remainings;
        int common = 0;
        FORD(i,SZ(pairs)-1,0) {
            if ((mask >> i) & 1) {
                common = common * 10 + pairs[i];
            } else {
                ds.push_back(pairs[i]);
                ds.push_back(pairs[i]);
            }
        }
        if (__builtin_popcount(mask) && !common) continue;

        sort(ALL(ds));

        REP(i,SZ(ds)-1) { // first different digits
            int j = i+1;

            int a = common * 10 + ds[i];
            int b = common * 10 + ds[j];
            if (!a || !b) continue;

            auto tmp = ds;
            tmp.erase(tmp.begin() + j);
            tmp.erase(tmp.begin() + i);

            res = min(res, construct(tmp, max(a, b), min(a, b)));
        }
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        string s; cin >> s;
        vector<int> digits;
        for (char c : s) digits.push_back(c - '0');
        sort(ALL(digits));

        cout << "Case #" << test << ": " << solve(digits) << endl;
        // DEBUG(brute(digits));
    }
    return 0;
}
