
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int id[TWO(10)][10];
int bad;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("automata.in", "r", stdin);
    freopen("automata.out", "w", stdout);
    int m;
    while (cin >> m) {
        int cur = 0;
        REP(mask,TWO(m)) REP(i,m) id[mask][i] = ++cur;
        bad = ++cur;

        cout << cur << ' ' << id[0][0] << '\n';
        cout << 1 << ' ' << id[0][0] << '\n';
        REP(mask,TWO(m)) REP(i,m) {
            // H
            int x = bad;
            if (!CONTAIN(mask, i)) {
                int mask2 = mask + TWO(i);
                int i2 = (i + 1) % m;
                x = id[mask2][i2];
            }
            // V
            int y = bad;
            if (i < m-1 && !CONTAIN(mask, i) && !CONTAIN(mask, i+1)) {
                int mask2 = mask + TWO(i+1);
                int i2 = (i + 1) % m;
                y = id[mask2][i2];
            }
            // S
            int z = bad;
            if (CONTAIN(mask,i)) {
                int mask2 = mask - TWO(i);
                int i2 = (i + 1) % m;
                z = id[mask2][i2];
            }

            cout << x << ' ' << y << ' ' << z << '\n';
        }
        cout << bad << ' ' << bad << ' ' << bad << '\n';
        cout << endl;
    }
}
