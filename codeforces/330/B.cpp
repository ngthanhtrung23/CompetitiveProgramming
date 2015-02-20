
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

int n, m;
bool bad[1011][1011];

int main() {
    while (cin >> n >> m) {
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            bad[u][v] = bad[v][u] = true;
        }

        FOR(center,1,n) {
            bool ok = true;
            FOR(i,1,n) if (i != center && bad[i][center]) ok = false;

            if (ok) {
                cout << n-1 << endl;
                FOR(i,1,n) if (i != center) cout << center << ' ' << i << endl;
                break;
            }
        }
    }
    return 0;
}
