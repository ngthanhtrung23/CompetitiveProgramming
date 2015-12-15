
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

int E, Es, Ef;
ll f[10111000];

ll getF(int e) {
    if (e <= 0) return 0;
    return f[e];
}

bool check(double x) {
    ll k = (225.0 - 25.0) / x;
    if (225 - k*x > 25 && 225 - (k+1)*x > 0) ++k;
    return k <= f[E];
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(6);
    while (cin >> E >> Es >> Ef) {
        f[0] = 0;
        FOR(i,1,E) {
            ll x = getF(i - Ef) + 1;
            f[i] = getF(i - Es) + x;
            if (f[i] > 1e18) f[i] = 1e18;
        }
        double l = 0.0, r = 225;
        REP(turn,1000) {
            double mid = (l + r) / 2.0;
            if (check(mid)) r = mid;
            else l = mid;
        }
        cout << (l + r) / 2.0 << endl;
    }
}
