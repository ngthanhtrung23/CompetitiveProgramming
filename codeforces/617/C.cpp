
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

ll d1[MN], d2[MN], x[MN], y[MN];
int n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    ll x1, y1, x2, y2;
    while (cin >> n >> x1 >> y1 >> x2 >> y2) {
        FOR(i,1,n) {
            cin >> x[i] >> y[i];
            d1[i] = sqr(x[i] - x1) + sqr(y[i] - y1);
            d2[i] = sqr(x[i] - x2) + sqr(y[i] - y2);
        }

        ll res = 1e18;
        FOR(u,0,n) {
            ll du = d1[u];
            ll dv = 0;

            FOR(i,1,n) if (d1[i] > du) dv = max(dv, d2[i]);

            res = min(res, du + dv);
        }
        cout << res << endl;
    }
}
