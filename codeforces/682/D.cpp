#include <bits/stdc++.h>
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

const int MN = 1011;

int f[22][MN][MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int la, lb;
    string a, b;
    int k;
    while (cin >> la >> lb >> k >> a >> b) {
        a = " " + a + " ";
        b = " " + b + " ";
        memset(f, 0, sizeof f);
        FOR(t,1,2*k) {
            FOR(i,1,la) FOR(j,1,lb) {
                if (t % 2 == 1) {
                    if (a[i] == b[j]) {
                        f[t][i][j] = max(f[t][i-1][j-1], f[t-1][i-1][j-1]) + 1;
                    }
                    else f[t][i][j] = 0;
                }
                else {
                    f[t][i][j] = max(f[t][i-1][j], f[t][i][j-1]);
                    f[t][i][j] = max(f[t][i][j], f[t-1][i][j]);
                }
            }
        }
        int res = 0;
        FOR(i,1,la) FOR(j,1,lb) {
            res = max(res, f[2*k-1][i][j]);
        }
        cout << res << endl;
    }
}
