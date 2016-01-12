
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 2011;

ll x[MN], y[MN];
int n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n;
        FOR(i,1,n) {
            cin >> x[i] >> y[i];
        }
        ll res = 0;
        FOR(i,1,n) {
            unordered_map<ll,ll> cnt;
            FOR(j,1,n) if (j != i) {
                cnt[ sqr(x[i] - x[j]) + sqr(y[i] - y[j]) ] += 1;
            }

            for(auto p : cnt)
                res += p.second * (p.second - 1) / 2LL;
        }
        cout << "Case #" << test << ": " << res << endl;
    }
}