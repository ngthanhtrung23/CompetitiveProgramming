
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

int typ[2011];
int n, P[4], T1, T2;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> P[1] >> P[2] >> P[3] >> T1 >> T2) {
        int nn = 2000, ln = 0;
        FOR(i,0,2000) typ[i] = 3;

        FOR(i,1,n) {
            int l, r; cin >> l >> r;
            ++l;
            nn = min(nn, l);
            ln = max(ln, r);

            FOR(i,l,r) typ[i] = min(typ[i], 1);
            FOR(i,r+1,r+T1) typ[i] = min(typ[i], 1);

            FOR(i,r+T1+1,r+T1+T2) typ[i] = min(typ[i], 2);
        }
        int res = 0;
        FOR(i,nn,ln) res += P[typ[i]];
        cout << res << endl;
    }
}
