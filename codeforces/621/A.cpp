
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

int n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        vector<ll> odd;
        ll sum = 0;
        FOR(i,1,n) {
            ll a; cin >> a;
            if (a % 2 == 0) sum += a;
            else odd.push_back(a);
        }
        sort(odd.begin(), odd.end());
        if (SZ(odd) % 2) odd.erase(odd.begin());

        for(auto t : odd) sum += t;
        cout << sum << endl;
    }
}
