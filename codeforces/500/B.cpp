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

const int MN = 311;
struct DSU {
    int lab[MN];
    void init() {
        memset(lab, -1, sizeof lab);
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

int a[311], pos[311], res[311];
int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i];
            pos[a[i]] = i;
        }
        DSU dsu;
        dsu.init();
        FOR(i,1,n) FOR(j,1,n) {
            char c; cin >> c;
            if (c == '1') dsu.merge(i, j);
        }
        FOR(i,1,n) {
            FOR(x,1,n) if (pos[x] > 0 && dsu.getRoot(pos[x]) == dsu.getRoot(i)) {
                pos[x] = -1;
                res[i] = x;
                break;
            }
        }
        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}
