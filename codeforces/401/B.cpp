#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int x, k, mark[4011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> x >> k) {
        memset(mark, false, sizeof mark);
        mark[x] = true;
        FOR(i,1,k) {
            int typ; cin >> typ;
            if (typ == 1) {
                int u, v; cin >> u >> v;
                mark[u] = mark[v] = true;
            }
            else {
                int u; cin >> u;
                mark[u] = true;
            }
        }

        int ln = 0;
        FOR(i,1,x) if (!mark[i]) ++ln;
        int nn = 0;
        FOR(i,1,x) if (!mark[i]) {
            ++nn;
            mark[i] = mark[i+1] = true;
        }
        cout << nn << ' ' << ln << endl;
    }
    return 0;
}
