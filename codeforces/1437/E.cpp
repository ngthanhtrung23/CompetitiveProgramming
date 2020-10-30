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

// non-decreasing
int lis(const vector<int>& a) {
    multiset<int> s;
    multiset<int> :: iterator it;

    for (int x : a) {
        s.insert(x);
        it = s.upper_bound(x);
        if (it != s.end()) s.erase(it);
    }
    return SZ(s);
}

int get(const vector<int>& a, int lower, int upper) {
    if (a.empty()) return 0;

    vector<int> good;
    int bad = 0;
    REP(i,SZ(a)) {
        int x = a[i];
        if (lower + i < x && x < upper - (SZ(a) - 1 - i)) {
            good.push_back(x - i);
        } else ++bad;
    }

    return good.size() - lis(good) + bad;
}

int solve(const vector<int>& a, const vector<int>& blocked) {
    if (SZ(blocked) >= 2) {
        REP(i,SZ(blocked)-1) {
            int l = blocked[i];
            int r = blocked[i+1];
            if (a[l] + (r - l) > a[r]) return -1;
        }
    }

    const int INF = 1e9 + 11;
    if (SZ(blocked) == 0) {
        return get(a, -INF, INF);
    }

    int res = get(
        vector<int> (a.begin(), a.begin() + blocked[0]),
        -INF,
        a[blocked[0]]);

    res += get(
        vector<int> (a.begin() + blocked.back() + 1, a.end()),
        a[blocked.back()],
        INF);
    
    REP(i,SZ(blocked)-1) {
        res += get(
            vector<int> (a.begin() + blocked[i] + 1, a.begin() + blocked[i+1]),
            a[blocked[i]],
            a[blocked[i+1]]);
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n, nBlocked;
    while (cin >> n >> nBlocked) {
        vector<int> a(n);
        for (auto& val : a) cin >> val;

        vector<int> blocked(nBlocked);
        for (auto& b : blocked) {
            cin >> b;
            --b;
        }

        cout << solve(a, blocked) << '\n';
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
