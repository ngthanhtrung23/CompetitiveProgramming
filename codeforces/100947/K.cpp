
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

int res[111*111], a[111][111], n;

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];

        int cur = 0;
        FOR(sum,2,n+n) {
            if (sum % 2 == 0) {
                FORD(i,n,1) {
                    int j = sum - i;
                    if (j >= 1 && j <= n) res[++cur] = a[i][j];
                }
            }
            else {
                FOR(i,1,n) {
                    int j = sum - i;
                    if (j >= 1 && j <= n) res[++cur] = a[i][j];
                }
            }
        }

        FOR(i,1,n) {
            FOR(j,1,n) printf("%lld ", res[(i-1)*n+j]);
            puts("");
        }
    }
}
