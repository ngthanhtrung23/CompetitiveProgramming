
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

int n, x[311], y[311];

int ccw(int i, int j, int k) {
    int t = (y[j] - y[i]) * (x[k] - x[i])
          - (y[k] - y[i]) * (x[j] - x[i]);
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}

int order(int i, int j, int k) {
    return min(x[i], x[k]) <= x[j] && x[j] <= max(x[i], x[k])
        && min(y[i], y[k]) <= y[j] && y[j] <= max(y[i], y[k]);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("cottages.in", "r", stdin);
    freopen("cottages.out", "w", stdout);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d%d", &x[i], &y[i]);

        int res = 0;
        FOR(i,1,n) {
            FOR(j,i+1,n) {
                bool can = true;
                FOR(k,1,n) if (k != i && k != j) {
                    if (ccw(i, j, k) == 0 && order(i, k, j)) {
                        can = false;
                        break;
                    }
                }
                if (can) {
                    ++res;
                }
            }
        }
        cout << res * 2 << endl;
    }
}
