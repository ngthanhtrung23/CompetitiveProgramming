
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

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 1011;
int x[MN], y[MN], nx, ny;
int f[MN][MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> nx >> ny) {
        --nx; --ny;
        FOR(i,1,nx) cin >> x[i];
        FOR(i,1,ny) cin >> y[i];
        sort(x+1, x+nx+1, greater<int>());
        sort(y+1, y+ny+1, greater<int>());

        FOR(i,0,nx) FOR(j,0,ny) {
            if (i == 0 && j == 0) f[i][j] = 0;
            else if (i == 0) {
                f[0][j] = f[0][j-1] + y[j];
            }
            else if (j == 0) {
                f[i][0] = f[i-1][0] + x[i];
            }
            else {
                f[i][j] = min(
                        f[i-1][j] + x[i] * (j+1),
                        f[i][j-1] + y[j] * (i+1)
                        );
            }
        }
        cout << f[nx][ny] << endl;
    }
}
