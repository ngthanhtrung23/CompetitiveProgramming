#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

int a[1011][1011], m, n, k;

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> m >> n >> k) {
        int ok = 0;
        memset(a, 0, sizeof a);
        FOR(turn,1,k) {
            int u, v;
            cin >> u >> v;
            a[u][v] = 1;

            if (ok) continue;

            FOR(i,u-1,u) FOR(j,v-1,v)
                if (a[i][j] + a[i][j+1] + a[i+1][j] + a[i+1][j+1] == 4) {
                    ok = turn;
                }
        }
        cout << ok << endl;
    }
    return 0;
}
