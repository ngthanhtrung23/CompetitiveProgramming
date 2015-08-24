#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 300111;
struct DSU {
    int lab[MN];
    void init(int n) {
        REP(i,n+1) lab[i] = -1;
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
int n, m, q;
int g[MN], t[MN], res[MN];
vector<int> ke[MN];
const int INF = 1e9 + 7;
vector<int> rem[MN];
bool alive[MN];

DSU dsu;
void add(int u) {
    for(int v : ke[u]) if (alive[v]) {
        dsu.merge(u, v);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> q) {
        FOR(i,1,n) ke[i].clear();

        t[1] = INF; FOR(i,2,n) cin >> t[i];
        FOR(i,1,q) cin >> g[i];
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        FOR(i,1,q) rem[i].clear();

        set< pair<int,int> > all;
        FOR(i,1,n) all.insert(make_pair(t[i], i));

        FOR(i,1,n) alive[i] = true;
        FOR(i,1,q) {
            while (all.begin()->first < g[i]) {
                int u = all.begin()->second;
                rem[i].push_back(u);
                all.erase(all.begin());

                alive[u] = false;
            }
//            PR0(rem[i], rem[i].size());
        }

        dsu.init(n);
        FOR(i,1,n) if (alive[i]) add(i);
        FORD(i,q,1) {
            int x = dsu.getRoot(1);
            res[i] = -dsu.lab[x];

            for(int u : rem[i]) {
                alive[u] = true;
            }
            for(int u : rem[i])
                add(u);
        }

        FOR(i,1,q) printf("%I64d ", g[i] * (ll) res[i]); puts("");
    }
}

