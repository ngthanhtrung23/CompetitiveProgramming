
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
#define TWO(X) (1LL<<(X))

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int n; cin >> n;
    vector<int> a(n);
    vector<int> len(n);
    REP(i,n) {
        string s; cin >> s;
        for (char c : s) {
            a[i] ^= TWO(c - 'a');
        }
        len[i] = SZ(s) % 2;
    }
    map<pair<int,int>,int> cnt;
    int res = 0;
    REP(i,n) {
        res += cnt[make_pair(a[i], len[i])];
        REP(c,26) {
            res += cnt[make_pair(a[i] ^ TWO(c), 1 - len[i])];
        }
        cnt[make_pair(a[i], len[i])]++;
    }
    cout << res << endl;
    return 0;
}
