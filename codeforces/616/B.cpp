
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

const int MN = 111;
int m, n, a[MN][MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> m >> n) {
        int res = 0;
        FOR(i,1,m) {
            FOR(j,1,n) cin >> a[i][j];
            res = max(res, *min_element(a[i]+1, a[i]+n+1));
        }
        cout << res << endl;
    }
}
