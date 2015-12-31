
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
    ll n;
    while (cin >> n) {
        int res = 0;
        if (n % 2) res = 0;
        else {
            int t = n / 2;
            if (t % 2) res = t / 2;
            else res = t / 2 - 1;
        }
        cout << res << endl;
    }
}
