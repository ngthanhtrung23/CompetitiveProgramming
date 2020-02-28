
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

void solve(int n, int a, int na, int b, int nb) {
    vector<int> res;
    int cur = 1;
    FOR(i,1,na) {
        FOR(val,cur+1,cur+a-1) res.push_back(val);
        res.push_back(cur);

        cur += a;
    }
    FOR(i,1,nb) {
        FOR(val,cur+1,cur+b-1) res.push_back(val);
        res.push_back(cur);

        cur += b;
    }
    assert(cur == n+1);

    for (int x : res) cout << x << ' '; cout << endl;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int n, a, b;
    while (cin >> n >> a >> b) {
        try {
            FOR(na,0,n) {
                int nb = (n - na * a) / b;
                if (nb < 0) continue;
                if (a*na + b*nb == n) {
                    solve(n, a, na, b, nb);
                    throw 1;
                }
            }
            cout << -1 << endl;
        } catch (...) {
        }
    }
    return 0;
}
