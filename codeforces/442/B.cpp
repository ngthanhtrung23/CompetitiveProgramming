#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

double p[111], prod[111][111];

double get(int i, int j) {
    if (i > j) return 1.0;
    return prod[i][j];
}

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> p[i];
        sort(p+1, p+n+1);

        FOR(i,1,n) FOR(j,1,n) {
            prod[i][j] = 1.0;
            FOR(k,i,j) prod[i][j] *= (1 - p[k]);
        }

        double res = 0.0;
        FOR(i,1,n) FOR(j,i,n) {
            double cur = 0.0;
            FOR(k,i,j) {
                cur += p[k] * get(i,k-1) * get(k+1,j);
            }
            res = max(res, cur);
        }
        cout << (fixed) << setprecision(10) << res << endl;
    }
    return 0;
}
