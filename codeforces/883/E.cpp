
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
#define CONTAIN(S,X) (((S) >> (X)) & 1)

bool has[300];

bool check(string s, string pat) {
    assert(SZ(s) == SZ(pat));
    REP(i,SZ(s)) {
        if (pat[i] == '*' || pat[i] == s[i]) continue;

        return false;
    }
    REP(i,SZ(s)) {
        if (pat[i] == '*' && has[s[i]]) return false;
    }
    return true;
}

int mask(string s, string pat) {
    int res = 0;
    REP(i,SZ(s)) {
        if (pat[i] == '*') {
            res |= TWO(s[i] - 'a');
        }
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int len; cin >> len;
    string pat; cin >> pat;
    for (char c : pat) has[c] = true;

    int mask_all = TWO(26) - 1;
    int nword; cin >> nword;
    while (nword--) {
        string s; cin >> s;
        if (check(s, pat)) {
            mask_all &= mask(s, pat);
        }
    }
    cout << __builtin_popcountll(mask_all) << endl;
    return 0;
}
