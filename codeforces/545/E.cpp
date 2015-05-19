
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
vector< pair<int,int> > ke[MN];
long long d[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        map< pair<int,int>, int> ids;
        FOR(i,1,m) {
            int u, v, c; cin >> u >> v >> c;
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));

            ids[make_pair(u, v)] = i;
            ids[make_pair(v, u)] = i;
        }
        int start; cin >> start;

        // Dijkstra
        set< pair<long long, int> > s;
        FOR(i,1,n) d[i] = 1000111000111000111LL;
        d[start] = 0;
        s.insert(make_pair(0, start));

        while (!s.empty()) {
            auto cur = *s.begin(); s.erase(s.begin());
            if (cur.first != d[cur.second]) continue;

            int u = cur.second;
            long long l = cur.first;

            for(auto p : ke[u]) {
                int v = p.first;
                if (d[v] > l + p.second) {
                    d[v] = l + p.second;
                    s.insert(make_pair(d[v], v));
                }
            }
        }
        
        // Find tree
        vector< pair<long long, int> > vertices;
        FOR(i,1,n) {
            vertices.push_back(make_pair(d[i], i));
        }
        sort(vertices.begin(), vertices.end());

        long long sum = 0;
        vector< int> res;
        for(auto p : vertices) {
            int u = p.second;
            if (u == start) continue;

            int best = 1000111000, save = -1;
            for(auto e : ke[u]) {
                int v = e.first;
                if (d[v] + e.second == d[u]) {
                    if (e.second < best) {
                        best = e.second;
                        save = v;
                    }
                }
            }
            res.push_back(ids[make_pair(u, save)]);
            sum += best;
        }
        cout << sum << endl;
        for(int x : res) cout << x << ' '; cout << endl;
    }
    return 0;
}
