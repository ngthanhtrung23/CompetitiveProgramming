
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

int V;
vector<int> G[MN];

struct DirectedDfs {
    vector<int> num, low, current, S;
    int counter;
    vector< vector<int> > scc;

    DirectedDfs() : num(V, -1), low(V, 0), current(V, 0), counter(0) {
        REP(i,V) if (num[i] == -1) dfs(i);
    }

    void dfs(int u) {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        REP(j, G[u].size()) {
            int v = G[u][j];
            if (num[v] == -1) dfs(v);
            if (current[v]) low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            scc.push_back(vector<int>());
            while (1) {
                int v = S.back(); S.pop_back(); current[v] = 0;
                scc.back().push_back(v);
                if (u == v) break;
            }
        }
    }
};

int n, m, id[MN], isLoop[MN], lab[MN];
pair<int,int> e[MN];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    u = getRoot(u); v = getRoot(v);
    if (u == v) return ;
    
    if (lab[u] > lab[v]) swap(u, v);

    lab[u] += lab[v];
    lab[v] = u;
    isLoop[u] += isLoop[v];
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        V = n;
        FOR(i,0,n) G[i].clear();
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            --u; --v;
            G[u].push_back(v);
            e[i] = make_pair(u, v);
        }
        DirectedDfs tree;

        int cur = 0;
        memset(lab, -1, sizeof lab);
        memset(isLoop, 0, sizeof isLoop);
        for(auto scc : tree.scc) {
            ++cur;
            for(int x : scc) {
                id[x] = cur;
                if (scc.size() > 1) isLoop[cur] = 1;
            }
            lab[cur] = -scc.size();
        }

        FOR(i,1,m) {
            int u = id[e[i].first], v = id[e[i].second];
            if (u != v) merge(u, v);
        }

        int res = 0;
        FOR(i,1,cur) if (lab[i] < 0) {
            if (isLoop[i]) res -= lab[i];
            else res -= lab[i] + 1;
        }
        cout << res << endl;
    }
    return 0;
}
