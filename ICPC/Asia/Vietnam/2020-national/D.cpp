#include "bits/stdc++.h"
#include <sys/resource.h>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()

struct Edge {
    int to, cost;
};

const int MN = 300111;
const int INF = (int) 1e12;
pair<int,int> down[3][MN];
pair<int,int> child_diam[2][MN];
int up[MN], diam[MN], up_diam[MN];

void upMax(int& f, int val) {
    if (val > f) f = val;
}
void upMin(int& f, int val) {
    if (val < f) f = val;
}

// Compute
// - diam[u]: diameter of subtree at u
// - down[t][u]: must go down, to different children
void dfs1(int u, int fu, const vector<vector<Edge>>& adj) {
    diam[u] = 0;
    REP(t,3) down[t][u] = {-INF, -1};
    REP(t,2) child_diam[t][u] = {-INF, -1};

    for (const auto& e : adj[u]) {
        const int v = e.to;
        if (v == fu) continue;

        dfs1(v, u, adj);

        pair<int, int> down_to_v = {e.cost + max(0LL, down[0][v].first), v};
        REP(t,3) {
            if (down_to_v > down[t][u]) {
                FORD(t2,2,t+1) {
                    down[t2][u] = down[t2-1][u];
                }
                down[t][u] = down_to_v;
                break;
            }
        }
        auto cur_child_diam = make_pair(diam[v], v);
        if (cur_child_diam > child_diam[0][u]) {
            child_diam[1][u] = child_diam[0][u];
            child_diam[0][u] = cur_child_diam;
        } else if (cur_child_diam > child_diam[1][u]) {
            child_diam[1][u] = cur_child_diam;
        }

        upMax(diam[u], diam[v]);
    }
    upMax(diam[u], down[0][u].first);
    upMax(diam[u], down[0][u].first + down[1][u].first);
}

// Compute up[u] = longest path, does not go in subtree(u)
// Compute up_diam[u] = diam if do not use edge (fu, u) and subtree(u)
void dfs2(int u, int fu, int fcost, const vector<vector<Edge>>& adj, int& res) {
    if (fu != -1) {
        int paths_from_fu[3] = {up[fu], -INF, -INF};
        int npath = 1;

        REP(t,3) {
            if (down[t][fu].second != u) {
                paths_from_fu[npath] = down[t][fu].first;
                npath++;
                if (npath == 3) break;
            }
        }

        up[u] = 0;
        REP(t,3) upMax(up[u], fcost + paths_from_fu[t]);

        up_diam[u] = 0;
        upMax(up_diam[u], up_diam[fu]);
        if (child_diam[0][fu].second != u) {
            upMax(up_diam[u], child_diam[0][fu].first);
        } else {
            upMax(up_diam[u], child_diam[1][fu].first);
        }
        REP(t1,3) FOR(t2,t1+1,2) {
            upMax(up_diam[u], paths_from_fu[t1]);
            upMax(up_diam[u], paths_from_fu[t1] + paths_from_fu[t2]);
        }

        res = min(res, llabs(diam[u] - up_diam[u]));
    }

    for (const auto& e: adj[u]) {
        const int v = e.to;
        if (v == fu) continue;

        dfs2(v, u, e.cost, adj, res);
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    rlimit R;
    getrlimit(RLIMIT_STACK, &R);
    R.rlim_cur = R.rlim_max;
    setrlimit(RLIMIT_STACK, &R);

    int n;
    while (cin >> n && n) {
        vector<vector<Edge>> adj(n);
        REP(i,n-1) {
            int p, c; cin >> p >> c;
            --p;
            adj[p].push_back(Edge{i+1, c});
        }

        dfs1(0, -1, adj);

        int res = diam[0];
        up[0] = 0;
        dfs2(0, -1, 0, adj, res);
        cout << res << endl;
    }
}
