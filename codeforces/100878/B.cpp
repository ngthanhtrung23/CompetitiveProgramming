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
#define double long double
using namespace std;

const int MN = 3011;

double f[MN], pr[MN], pk[MN], p1k[MN];
int n, k;
double p;
double c[MN][MN];

void init() {
    FOR(i,0,MN-1) {
        c[i][0] = 1.0;
        FOR(j,1,i) c[i][j] = c[i-1][j-1] + c[i-1][j];
    }
}

double binom(int k, int n, double p) {
    return c[n][k] * pk[k] * p1k[n-k];
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    init();
    cout << (fixed) << setprecision(9);
    FOR(test,1,ntest) {
        cin >> n >> k >> p;

        pk[0] = 1.0;
        p1k[0] = 1.0;
        FOR(i,1,n) {
            pk[i] = pk[i-1] * p;
            p1k[i] = p1k[i-1] * (1.0 - p);
        }

        FOR(i,1,n) {
            pr[i] = 0.0;
            FOR(x,k,i) {
                pr[i] += binom(x, i, p);
            }
        }

        FOR(i,1,n) {
            f[i] = 0.0;
            FOR(j,0,i-1) f[i] = max(f[i], f[j] + pr[i-j]);
        }
        cout << "Case #" << test << ": " << f[n] << endl;
    }
}
