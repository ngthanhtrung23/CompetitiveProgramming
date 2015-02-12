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

const int MN = 300111;

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
} dsu;

vector<int> colors[MN];
int sum[MN];
map<int,int> cache[MN];
tuple< int,int,int> edges[MN];
int n, m, q;

void init() {
    memset(sum, 0, sizeof sum);
    REP(i,MN) {
        colors[i].clear();
        cache[i].clear();
    }
}

int nId;

int getId(int c, int u) {
    auto t = lower_bound(colors[u].begin(), colors[u].end(), c);
    if (*t != c) return -1;
    return sum[u-1] + t - colors[u].begin() + 1;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        init();
        nId = 0;
        FOR(i,1,m) {
            int a, b, c; cin >> a >> b >> c;
            colors[a].push_back(c);
            colors[b].push_back(c);
            edges[i] = make_tuple(a, b, c);
        }

        FOR(a,1,n) {
            sort(colors[a].begin(), colors[a].end());
            colors[a].resize(unique(colors[a].begin(), colors[a].end()) - colors[a].begin());
            sum[a] = sum[a-1] + colors[a].size();
        }

        dsu.init();
//        cout << "DONE INIT" << endl;
        FOR(i,1,m) {
            int a = get<0>(edges[i]),
                b = get<1>(edges[i]),
                c = get<2>(edges[i]);

            int u = getId(c, a), v = getId(c, b);
            dsu.merge(u, v);
        }
//        cout << "DONE ADD EDGES" << endl;

        cin >> q;
        while (q--) {
            int u, v; cin >> u >> v;
            int res = 0;
            if (cache[u].count(v)) res = cache[u][v];
            else {
                if (colors[u].size() > colors[v].size()) swap(u, v);
                for(int c : colors[u]) {
                    int x = getId(c, u), y = getId(c, v);
                    if (x >= 0 && y >= 0 && dsu.getRoot(x) == dsu.getRoot(y)) ++res;
                }
                cache[u][v] = cache[v][u] = res;
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
