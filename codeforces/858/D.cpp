
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()

#define hash hhh
pair<int,int> hash(const string& s, int l, int r) {
    int res = 1;
    FOR(i,l,r) {
        res = res * 10 + s[i] - '0';
    }
    return make_pair(r - l + 1, res);
}

string s[70111];
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int n; cin >> n;
    map<pair<int,int> ,int> cnt;
    FOR(i,1,n) {
        cin >> s[i];
        set<pair<int,int>> my;
        FOR(l,0,8) FOR(r,l,8) {
            my.insert(hash(s[i], l, r));
        }
        for (auto p : my) cnt[p]++;
    }

    FOR(i,1,n) {
        FOR(len,1,9) {
            bool found = false;
            FOR(l,0,8) {
                if (l + len - 1 <= 8) {
                    if (cnt[hash(s[i], l, l + len - 1)] == 1) {
                        cout << s[i].substr(l, len) << '\n';
                        found = true;
                        break;
                    }
                }
            }
            if (found) break;
        }
    }

    return 0;
}
