
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

const int MN = 100111;

unordered_map<int,int> lab[MN], attached[MN];
unordered_map< int, int> cache[MN];
unordered_set<int> colors[MN];
int n, m, q;

int getRoot(int color, int u) {
    if (!lab[color].count(u)) return u;
    return lab[color][u] = getRoot(color, lab[color][u]);
}

void merge(int color, int u, int v) {
    u = getRoot(color, u);
    v = getRoot(color, v);
    if (u != v) {
        if (!attached[color].count(u)) attached[color][u] = 0;
        if (!attached[color].count(v)) attached[color][v] = 0;
        if (attached[color][u] < attached[color][v]) swap(u, v);

        lab[color][u] = v;
        attached[color][u] += attached[color][v];
    }
}

void init() {
    REP(i,MN) {
        lab[i].clear();
        cache[i].clear();
    }
    FOR(i,1,n) colors[i].clear();
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m) {
        init();
        FOR(e,1,m) {
            int a, b, c; cin >> a >> b >> c;
            colors[a].insert(c);
            colors[b].insert(c);

            merge(c, a, b);
        }
        cin >> q;
        while (q--) {
            int u, v; cin >> u >> v;
            if (cache[u].count(v)) printf("%d\n", cache[u][v]);
            else {
                if (colors[u].size() > colors[v].size()) swap(u, v);
                int res = 0;
                for(int c : colors[u]) {
                    if (getRoot(c, u) == getRoot(c, v)) ++res;
                }
                cache[u][v] = cache[v][u] = res;
                printf("%d\n", res);
            }
        }
    }
    return 0;
}
