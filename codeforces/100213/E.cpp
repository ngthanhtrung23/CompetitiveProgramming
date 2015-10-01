
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 50111;
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

int n, s;
pair<int,int> a[MN];
map< pair<int,int>,int > id;

vector< pair<int,int> > get_neighbours(pair<int,int> cur) {
    vector< pair<int,int> > res;
    res.emplace_back(cur.first, cur.second - 1);
    res.emplace_back(cur.first, cur.second + 1);

    if (cur.first % 2) {
        for(int dx = -1; dx <= 1; dx += 2) {
            FOR(dy,0,1) {
                res.emplace_back(cur.first + dx, cur.second + dy);
            }
        }
    }
    else {
        for(int dx = -1; dx <= 1; dx += 2) {
            FOR(dy,-1,0) {
                res.emplace_back(cur.first + dx, cur.second + dy);
            }
        }
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("islands.in", "r", stdin);
    freopen("islands.out", "w", stdout);
    while (cin >> n >> s) {
        id.clear();
        FOR(i,1,n) {
            cin >> a[i].first >> a[i].second;
            if (!id.count(a[i])) id[a[i]] = i;
        }

        set< pair<int,int> > lands;
        DSU dsu; dsu.init(n);
        FOR(i,1,n) {
            if (lands.count(a[i])) continue; // cell is already land, ignore

            vector< pair<int,int> > neigh = get_neighbours(a[i]);
            int sum = 0;

            set< int > tmp;
            for(auto p : neigh) {
                if (lands.count(p)) {
                    int u = id[p];
                    u = dsu.getRoot(u);

                    if (tmp.count(u)) continue;

                    tmp.insert(u);
                    sum -= dsu.lab[u];
                }
            }

            if (sum + 1 > s) continue;

            lands.insert(a[i]);
            int u = id[a[i]];
            for(auto p : neigh) {
                if (lands.count(p)) {
                    int v = id[p];

                    dsu.merge(u, v);
                }
            }
        }
        vector<int> res;
        FOR(i,1,n) {
            if (id[a[i]] == i && lands.count(a[i])) {
                int u = dsu.getRoot(i);
                if (u == i) res.push_back(-dsu.lab[i]);
            }
        }
        cout << SZ(res) << endl;
        sort(res.begin(), res.end());
        for(auto x : res) cout << x << ' '; cout << endl;
    }
}
