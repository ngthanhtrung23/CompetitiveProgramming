
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

int m, n, x, k;
int a[111][111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> m >> n >> x >> k) {
        memset(a, 0, sizeof a);
        FOR(i,1,x) {
            int u, v; cin >> u >> v;
            a[u][v] = 1;
        }
        FOR(i,1,m) FOR(j,1,n) a[i][j] = a[i-1][j] + a[i][j-1] - a[i-1][j-1] + a[i][j];

        int res = 0;
        FOR(i1,1,m) FOR(i2,i1,m)
            FOR(j1,1,n) FOR(j2,j1,n) {
                int cur = a[i2][j2] - a[i1-1][j2] - a[i2][j1-1] + a[i1-1][j1-1];
                if (cur >= k) res++;
            }
        cout << res << endl;
    }
}
