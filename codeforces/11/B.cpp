
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

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    // 0 --> 0
    // 1 --> -1, +1
    // 2 --> -3, -1, 1, 3
    // 3 --> -6, -4, -2, 0, 2, 4, 6

    ll x;
    while (cin >> x) {
        FOR(res,0,100111) {
            ll from = res * (res +1LL) / 2;
            ll to = from;
            from = -from;

            if (x < from || x > to) continue;
            if (abs(x % 2) != abs(to % 2)) continue;

            cout << res << endl;
            break;
        }
    }
}
