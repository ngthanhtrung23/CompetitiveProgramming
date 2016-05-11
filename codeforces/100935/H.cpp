
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

int f[55][1011];

void init() {
    FOR(j,1,1000) f[1][j] = j;

    FOR(i,2,50) {
        FOR(j,1,1000) {
            f[i][j] = f[i-1][j-1] + 1 + f[i][j-1];
        }
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    init();
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int p, m; cin >> p >> m;
        int x = 1;
        while (f[p][x] < m) ++x;
        cout << "Case " << test << ": " << x << '\n';
    }
}
