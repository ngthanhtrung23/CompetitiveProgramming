
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

const int MN = 3011;
bool isLand[MN][2*MN];
int lab[MN*MN*2];
int m, n;

// r in [1, m], c in [1, 2*n]
int id(int r, int c) {
    return (r-1) * (n*2) + c;
}

int getRoot(int u) {
    if (lab[u] < 0) return u;
    while (lab[lab[u]] > 0) lab[u] = lab[lab[u]];
    return lab[u];
}

void merge(int u, int v) {
    u = getRoot(u); v = getRoot(v);
    if (u == v) return ;
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[u] = x;
        lab[v] = u;
    } else {
        lab[u] = v;
        lab[v] = x;
    }
}

int main() {
    int q;
    while (scanf("%d%d%d", &m, &n, &q) == 3) {
        memset(isLand, false, sizeof isLand);
        memset(lab, -1, sizeof lab);
        int res = 0;
        while (q--) {
            int u, v; scanf("%d%d", &u, &v);
            bool bad = false;
            unordered_set<int> s;
            FOR(di,-1,1) FOR(dj,-1,1) if (di || dj) {
                int uu = u + di, vv = v + dj;
                if (uu < 1 || uu > m) continue;

                if (vv == 0) vv = n+n;
                if (vv > n+n) vv = 1;

                if (!isLand[uu][vv]) continue;
                s.insert(getRoot(id(uu, vv)));
            }
            v += n;
            FOR(di,-1,1) FOR(dj,-1,1) if (di || dj) {
                int uu = u + di, vv = v + dj;
                if (uu < 1 || uu > m) continue;

                if (vv == 0) vv = n+n;
                if (vv > n+n) vv = 1;

                if (!isLand[uu][vv]) continue;
                if (s.count(getRoot(id(uu, vv)))) {
                    bad = true;
                }
            }
            v -= n;

            if (!bad) {
                ++res;
                isLand[u][v] = isLand[u][v+n] = true;
                REP(turn,2) {
                    FOR(di,-1,1) FOR(dj,-1,1) if (di || dj) {
                        int uu = u + di, vv = v + dj;
                        if (uu < 1 || uu > m) continue;

                        if (vv == 0) vv = n+n;
                        if (vv > n+n) vv = 1;

                        if (!isLand[uu][vv]) continue;
                        merge(id(uu, vv), id(u, v));
                    }
                    v += n;
                }
            }
        }
        if (n == 1) res = 0;
        cout << res << endl;
    }
    return 0;
}
