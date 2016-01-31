
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

const int MN = 55;
int a[MN][MN], x[MN], n;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];
        memset(x, 0, sizeof x);
        FOR(val,1,n) {
            FOR(i,1,n) if (x[i] == 0) { // can put at i?
                bool can = true;
                FOR(u,1,n) if (a[u][i] > val) can = false;
                FOR(v,1,n) if (a[i][v] > val) can = false;

                if (can) {
                    x[i] = val;
                    break;
                }
            }
        }
        FOR(i,1,n) cout << x[i] << ' '; cout << endl;
    }
}
