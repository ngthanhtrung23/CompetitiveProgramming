
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

const int inf = 1e9;
const int MN = 500;
struct Hungary {
    int nx, ny;
    ll cost[MN][MN], fx[MN], fy[MN];
    int matx[MN], which[MN];
    ll dist[MN];
    bool used[MN];

    void init(int _nx, int _ny) {
        nx = _nx; ny = max(_ny, _nx);
        memset(fx, 0, sizeof fx);
        memset(fy, 0, sizeof fy);
        memset(used, false, sizeof used);
        memset(matx, 0, sizeof matx);
        for(int i=0; i<=nx; ++i) for(int j=0; j<=ny; ++j) cost[i][j] = 0;
    }

    void add(int x, int y, ll c) { cost[x][y] = min(cost[x][y],c); }

    ll mincost() {
        for(int x = 1; x <= nx; ++x) {
            fx[x] = *min_element(cost[x]+1, cost[x]+ny+1);
        }
        for(int x=1; x<=nx; ++x) {
            int y0 = 0; matx[0] = x;
            for(int y=0; y<=ny; ++y) { dist[y] = inf + 1; used[y] = false; }

            do {
                used[y0] = true;
                int x0 = matx[y0];
                ll delta = inf + 1, y1;

                for(int y=1; y<=ny; ++y) if (!used[y]) {
                    ll curdist = cost[x0][y] - fx[x0] - fy[y];
                    if (curdist < dist[y]) {
                        dist[y] = curdist;
                        which[y] = y0;
                    }
                    if (dist[y] < delta) {
                        delta = dist[y];
                        y1 = y;
                    }
                }

                for(int y=0; y<=ny; ++y) if (used[y]) {
                    fx[matx[y]] += delta;
                    fy[y] -= delta;
                } else dist[y] -= delta;

                y0 = y1;
            } while (matx[y0] != 0);

            do {
                int y1 = which[y0];
                matx[y0] = matx[y1];
                y0 = y1;
            } while (y0);
        }
//      return -fy[0]; // nếu luôn đảm bảo có bộ ghép đầy đủ
        ll ret = 0;
        for(int y=1; y<=ny; ++y) {
            int x = matx[y];
            if (cost[x][y] < inf) ret += cost[x][y];
        }
        return ret;
    }
};


int n, m;
struct Edge {
    int u, v, c;
} e[MN];
vector<int> ke[66];
vector<int> res;

bool dfs(int u, int fu, int target) {
    if (u == target) return true;

    bool can = false;
    for(int edge_id : ke[u]) {
        int v = e[edge_id].v;
        if (v == u) v = e[edge_id].u;
        if (v == fu) continue;

        if (dfs(v, u, target)) {
            res.push_back(edge_id);
            can = true;
        }
    }
    return can;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("roads.in", "r", stdin);
    freopen("roads.out", "w", stdout);
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            cin >> e[i].u >> e[i].v >> e[i].c;
            if (i < n) {
                ke[ e[i].u ].push_back(i);
                ke[ e[i].v ].push_back(i);
            }
        }
        Hungary hungary;
        hungary.init(n-1, m-n+1);

        FOR(i,n,m) {
            // bfs e[i].u --> e[i].v
            res.clear();
            dfs(e[i].u, -1, e[i].v);

//            DEBUG(i);
//            PR0(res, res.size());

            for(auto x : res) {
                int cost = -e[x].c + e[i].c;
                hungary.add(x, i - n + 1, cost);
            }
        }
        ll res = -hungary.mincost();

        ll sum = 0;

        for(int y=1; y<=hungary.ny; ++y) {
            int x = hungary.matx[y];
            if (hungary.cost[x][y] < inf) {
//                cout << x << ' ' << y << endl;
                
                int u = x;
                int v = y + (n-1);
                e[u].c += hungary.fx[x];
                e[v].c -= hungary.fy[y];

                sum += abs(hungary.fx[x]);
                sum += abs(hungary.fy[y]);
            }
        }
        FOR(i,1,m) printf("%d\n", e[i].c);
    }
}

