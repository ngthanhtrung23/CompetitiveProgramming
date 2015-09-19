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

const int MN = 100111;

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

int n, m;
ll can;

pair<pair<int,int>, pair<int,int> > edges[MN];
bool used[MN];

int main() {
    ios :: sync_with_stdio(false);
    freopen("oil.in", "r", stdin);
    freopen("oil.out","w", stdout);
    while (cin >> n >> m >> can) {
        FOR(i,1,m) {
            cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first.first;
            edges[i].first.second = i;
        }
        sort(edges+1, edges+m+1);

        DSU dsu;
        dsu.init(n);
        FORD(i,m,1) {
            int u = edges[i].second.first, v = edges[i].second.second;
            if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

            used[i] = true;
            dsu.merge(u, v);
        }
        vector<int> res;
        FOR(i,1,m) if (!used[i]) {
            if (can < edges[i].first.first) break;

            can -= edges[i].first.first;
            res.push_back(edges[i].first.second);
        }
        cout << res.size() << endl;
        for(int x : res) cout << x << ' '; cout << endl;
    }
}