#include "bits/stdc++.h"

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
using namespace std;

const int MN = 500111;
int add[MN];

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    int n = (int) s.size();

    int q; cin >> q;
    while (q--) {
        int val, l, r; cin >> val >> l >> r;
        add[l] += val;
        add[r+1] -= val;
    }

    FOR(i,1,n) {
        add[i] += add[i-1];
    }

    FOR(i,1,n) {
        int u = s[i-1] - 'A';
        u = (u + add[i]) % 26;

        cout << (char) (u + 'A');
    }
    cout << endl;
    return 0;
}
