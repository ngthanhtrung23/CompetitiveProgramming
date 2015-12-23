
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

const int MN = 511;

int f[MN][MN];
int n, a[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FORD(i,n,1) FOR(j,i,n) {
            if (i == j) {
                f[i][j] = 1;
            }
            else if (i+1 == j) {
                if (a[i] == a[j]) f[i][j] = 1;
                else f[i][j] = 2;
            }
            else {
                if (a[i] == a[j]) f[i][j] = f[i+1][j-1];
                else f[i][j] = 1e9;

                FOR(k,i,j-1)
                    f[i][j] = min(f[i][j], f[i][k] + f[k+1][j]);
            }
        }
        cout << f[1][n] << endl;
    }
}
