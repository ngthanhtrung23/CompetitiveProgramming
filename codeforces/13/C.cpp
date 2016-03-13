
#include <bits/stdc++.h>
#define int long long
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

const int MN = 5011;
int a[MN], c[MN], n, nc;
int f[2][MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i];
            c[i] = a[i];
        }
        sort(c+1, c+n+1);
        nc = unique(c+1, c+n+1) - c - 1;
//        PR(c, nc);

        FOR(i,1,nc) f[1][i] = llabs(a[1] - c[i]);
        FOR(i,2,nc) f[1][i] = min(f[1][i], f[1][i-1]);

        FOR(i,2,n) {
            int cur = i % 2;
            FOR(j,1,nc) {
                f[cur][j] = f[1-cur][j] + llabs(a[i] - c[j]);
                if (j > 1) {
                    f[cur][j] = min(f[cur][j], f[cur][j-1]);
                }
            }
        }
        int res = f[n % 2][1];
        FOR(j,1,nc) res = min(res, f[n % 2][j]);
        cout << res << endl;
    }
}
