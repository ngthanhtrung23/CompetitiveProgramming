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
vector<int> ke[MN];
pair< pair<int,int>,int > edges[MN];
int n, sz[MN];

void dfs(int u, int fu) {
    sz[u] = 1;
    for(int v : ke[u]) {
        if (v == fu) continue;

        dfs(v, u);
        sz[u] += sz[v];
    }
}

double get(int u, int v, int c) {
    double res = 0;
    if (sz[u] > sz[v]) swap(u, v);
    
    double x = sz[u], y = n - sz[u];
    if (x >= 2 && y >= 1) {
        res += x * (x-1) * y * c;
    }
    if (y >= 2 && x >= 1) {
        res += y * (y-1) * x * c;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n-1) {
            int u, v, c;
            cin >> u >> v >> c;
            ke[u].push_back(v);
            ke[v].push_back(u);
            edges[i] = make_pair(make_pair(u, v), c);
        }
        dfs(1, -1);

        double cnt_all = n * (n-1LL) * (n-2LL) / 6;
        double res = 0;
        FOR(i,1,n-1) {
            res += get(edges[i].first.first, edges[i].first.second, edges[i].second);
        }
        int q; cin >> q;
        while (q--) {
            int i, val; cin >> i >> val;
            res -= get(edges[i].first.first, edges[i].first.second, edges[i].second);
            edges[i].second = val;
            res += get(edges[i].first.first, edges[i].first.second, edges[i].second);
            cout << res / (double) cnt_all << "\n";
        }
    }
    return 0;
}

