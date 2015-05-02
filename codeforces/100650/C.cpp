
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int m, n, k, a[22][22];

int encode(int i, int j) {
    return (i*n+j);
}

int main() {
    int test = 0;
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> k && m && n) {
        int need = 0;
        FOR(i,1,k) {
            int u, v; cin >> u >> v;
            need |= TWO(encode(u, v));
        }

        int cnt = 0;
        REP(mask,TWO(m*n)) {
            REP(i,m) REP(j,n) if (CONTAIN(mask,encode(i, j))) {
                a[i][j] = 1;
            }
            else a[i][j] = 0;

            int cur = 0;
            REP(i,m) REP(j,n) {
                int cnt = 0;
                FOR(di,-1,1) FOR(dj,-1,1) if (di || dj) {
                    int u = (i + di + m) % m;
                    int v = (j + dj + n) % n;

                    if (a[u][v]) ++cnt;
                }
                if (a[i][j]) if (cnt == 2 || cnt == 3) cur |= TWO(encode(i, j));
                if (!a[i][j] && cnt == 3) cur |= TWO(encode(i, j));
            }
            if (cur == need) ++cnt;
        }
        cout << "Case " << ++test << ": ";
        if (cnt == 0) cout << "Garden of Eden.\n";
        else {
            cout << cnt << " possible ancestors.\n";
        }
    }
    return 0;
}
