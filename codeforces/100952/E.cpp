
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

int a[22][22];
int m, n, t;
int bad[22][22];
int res;

void attempt(int cur) {
    if (cur > t) {
        ++res;
        return ;
    }
    FOR(i,1,m) FOR(j,1,n) if (!a[i][j]) {
        if (!bad[cur][a[i-1][j]]
                && !bad[cur][a[i+1][j]]
                && !bad[cur][a[i][j-1]]
                && !bad[cur][a[i][j+1]]) {

            a[i][j] = cur;
            attempt(cur+1);
            a[i][j] = 0;
        }
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> m >> n >> t;
        memset(bad, 0, sizeof bad);
        int p; cin >> p;
        while (p--) {
            int u, v; cin >> u >> v;
            bad[u][v] = bad[v][u] = 1;
        }

        res = 0;
        attempt(1);
        if (res == 0) cout << "impossible";
        else cout << res;
        cout << endl;
    }
}
