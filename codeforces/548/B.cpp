
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

int m, n, q, a[511][511], f[511][511], row[511];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> q) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        FOR(i,1,m) FOR(j,1,n)
            if (a[i][j] == 0) f[i][j] = 0;
            else f[i][j] = f[i][j-1] + 1;
        FOR(i,1,m) row[i] = *max_element(f[i]+1, f[i]+n+1);

        while (q--) {
            int u, v; cin >> u >> v;
            a[u][v] = 1 - a[u][v];

            FOR(j,1,n) {
                if (a[u][j] == 0) f[u][j] = 0;
                else f[u][j] = f[u][j-1] + 1;
            }
            row[u] = *max_element(f[u]+1, f[u]+n+1);
            printf("%d\n", *max_element(row+1, row+m+1));
        }
    }
    return 0;
}

