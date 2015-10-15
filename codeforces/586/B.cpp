
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int x[2][111], b[111], n, a[111], c[111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        memset(x, 0, sizeof x);
        memset(a, 0, sizeof a);
        memset(c, 0, sizeof c);

        REP(turn,2) FOR(i,1,n-1) cin >> x[turn][i];
        FOR(i,1,n) cin >> b[i];

        FOR(i,1,n) {
            a[i] = a[i-1] + x[0][i-1];
        }
        FORD(i,n,1) {
            c[i] = c[i+1] + x[1][i];
        }
        int res = 1e9;
        FOR(i,1,n) FOR(j,i+1,n)
            res = min(res, a[i] + a[j] + b[i] + b[j] + c[i] + c[j]);
        cout << res << endl;
    }
}
