
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int n, bx, by;
ll x[11];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> bx) {
        ll X = 0;
        FOR(i,1,n) cin >> x[i];
        FOR(i,1,n) X = X * bx + x[i];

        ll Y = 0;
        cin >> n >> by;
        FOR(i,1,n) cin >> x[i];
        FOR(i,1,n) Y = Y * by + x[i];

        if (X == Y) puts("=");
        else if (X < Y) puts("<");
        else puts(">");
    }
}
