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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int n;
double p[18][18];
double f[TWO(18)];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        REP(i,n) REP(j,n) cin >> p[i][j];

        REP(mask,TWO(n)) {
            if (!CONTAIN(mask,0)) {
                f[mask] = 0;
                continue;
            }
            if (mask == 1) {
                f[mask] = 1.0;
                continue;
            }

            f[mask] = 0;
            REP(i,n) if (CONTAIN(mask,i))
                REP(j,n) if (CONTAIN(mask,j) && i != j) {
                    f[mask] = max(f[mask],
                            p[j][i] * f[mask - TWO(i)] + p[i][j] * f[mask - TWO(j)]);
                }
        }
        cout << f[TWO(n) - 1] << endl;
    }
}
