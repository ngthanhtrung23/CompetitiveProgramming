#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
using namespace std;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);

    ll k, a, b;
    while (cin >> k >> a >> b) {
        ll from = (a / k) * k;
        while (from < a) from += k;
        while (from - k >= a) from -= k;

        ll to = (b / k) * k;
        while (to > b) to -= k;
        while (to + k <= b) to += k;

        cout << (to - from) / k + 1 << endl;
    }
}
