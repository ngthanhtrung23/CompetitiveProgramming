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

int32_t main() {
    ios::sync_with_stdio(0);

    int n; cin >> n;
    vector< pair<char, int> > events;
    FOR(i,1,2*n) {
        char c; cin >> c;
        int val = -1;
        if (c == '-') cin >> val;
        events.push_back({c, val});
    }
    set<int> cur;
    reverse(ALL(events));
    vector<int> res;
    for (auto [c, val] : events) {
        if (c == '-') {
            cur.insert(val);
            if (*cur.begin() != val) {
                cout << "NO" << endl;
                return 0;
            }
        } else {
            if (cur.empty()) {
                cout << "NO" << endl;
                return 0;
            }
            res.push_back(*cur.begin());
            cur.erase(cur.begin());
        }
    }
    reverse(ALL(res));
    cout << "YES" << endl;
    for (int x : res) cout << x << ' ';
    cout << endl;

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
