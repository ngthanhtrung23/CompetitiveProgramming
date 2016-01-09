
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

const int MN = 1000111;

int v[MN], c[MN], f[3][MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n) {
        memset(f, 0, sizeof f);
        FOR(i,1,n) {
            cin >> v[i] >> c[i];
            f[c[i]][v[i]]++;
        }
        REP(col,3) {
            FOR(i,1,1000 * 1000)
                f[col][i] += f[col][i-1];
        }

        int best = 1000111000;
        int savea = -1, saveb = -1;

        int min1_0 = 1000111000, a = -1;
        FOR(b,0,1000 * 1000) {
            int cur1_0 = f[1][b] - f[0][b];
            if (cur1_0 < min1_0) {
                min1_0 = cur1_0;
                a = b;
            }

            int cur = n + min1_0 - f[1][b] - (f[2][1000 * 1000] - f[2][b]);
            if (cur < best) {
                best = cur;
                saveb = b;
                savea = a;
            }
        }

        cout << savea << ' ' << saveb << endl;
    }
}
