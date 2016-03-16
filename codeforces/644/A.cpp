
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
#define SZ(x) ((int) (x).size())
using namespace std;

int x[111][111];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    int n, a, b;
    while (cin >> n >> a >> b) {
        if (n > a * b) {
            cout << -1 << endl;
        }
        else {
            memset(x, 0, sizeof x);
            int u = 1;
            FOR(i,1,a) FOR(j,1,b) {
                if ((i + j) % 2 == 0) {
                    if (u <= n) x[i][j] = u;
                    u += 2;
                }
            }
            u = 2;
            FOR(i,1,a) FOR(j,1,b) {
                if ((i + j) % 2 == 1) {
                    if (u <= n) x[i][j] = u;
                    u += 2;
                }
            }

            FOR(i,1,a) {
                FOR(j,1,b) cout << x[i][j] << ' ';
                cout << endl;
            }
        }
    }
}
