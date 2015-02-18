#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#define maxn 100005
using namespace std;

struct edge {
    int u,v,cost,index;
};

bool cmp(edge A,edge B) {
    return A.cost < B.cost;
}

edge makeEdge(int _u,int _v,int _cost,int _index) {
    edge E;
    E.u = _u;
    E.v = _v;
    E.cost = _cost;
    E.index = _index;
    return E;
}


edge graph[maxn];
int n;
int weight[maxn],par[maxn];

int root(int u) {
    if (u != par[u]) par[u] = root(par[u]);
    if (u != par[u]) weight[u] = weight[par[u]];
    return par[u];
}

void link(int u,int v) {
    u = root(u);
    v = root(v);
    if (u == v) return;
    par[v] = u;
    weight[u] += weight[v];
    weight[v] = weight[u];
}

struct bigTree {
    vector< pair<int,int> > adj[maxn];
    int numVer;
    int pos[maxn],bucket[maxn];
    long long coef[maxn],totalWeight[maxn];
    long long value[maxn],rootWeight;
    bool visit[maxn];

    void init() {
        memset(pos,-1,sizeof(pos));
        memset(value,0,sizeof(value));
        memset(visit,false,sizeof(visit));
        numVer = 0;
        for (int i = 1; i <= n; i++) adj[i].clear();
    }

    void clearOldGraph() {
        for (int i = 1; i <= numVer; i++) {
            pos[bucket[i]] = -1;
            adj[i].clear();
            visit[i] = false;
        }
        numVer = 0;
    }

    int get(int u) {
        if (pos[u] < 0) {
            numVer++;
            bucket[numVer] = u;
            pos[u] = numVer;
        }
        return pos[u];
    }

    void addEdge(int u,int v,int index) {
        int gu = get(root(u)),gv = get(root(v));
        coef[gu] = weight[root(u)];
        coef[gv] = weight[root(v)];
        adj[gu].push_back(make_pair(gv,index));
        adj[gv].push_back(make_pair(gu,index));
    }

    void firstDFS(int u,int pre) {
        visit[u] = true;        
        totalWeight[u] = coef[u];
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            if (v == pre) continue;         
            firstDFS(v,u);
            totalWeight[u] += totalWeight[v];
        }
        if (pre == -1) rootWeight = totalWeight[u];
    }

    void secondDFS(int u,int pre) {
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            if (v == pre) continue;
            secondDFS(v,u);
            value[adj[u][i].second] = totalWeight[v] * (rootWeight - totalWeight[v]);
        }
    }

    void solveNewGraph() {
        for (int i = 1; i <= numVer; i++) if (!visit[i]) {
            firstDFS(i,-1);
            secondDFS(i,-1);
        }
    }
} ts;

void solve() {
    ts.init();
    for (int i = 1; i <= n; i++) weight[i] = 1,par[i] = i;
    int LF = 1;
    while (LF < n) {
        int RF = LF + 1;
        while (RF < n && graph[LF].cost == graph[RF].cost) RF++;
        ts.clearOldGraph();
        for (int i = LF; i < RF; i++) {
            ts.addEdge(graph[i].u,graph[i].v,graph[i].index);
        }
        ts.solveNewGraph();
        for (int i = LF; i < RF; i++) link(graph[i].u,graph[i].v);
        LF = RF;
    }

    long long ret = -1;
    int cnt = 0;
    for (int i = 1; i < n; i++) if (ret < ts.value[i]) {
        ret = ts.value[i];
        cnt = 1;
    }
    else if (ret == ts.value[i]) cnt++;
    cout << ret * 2 << ' ' << cnt << endl;
    for (int i = 1; i < n; i++) if (ret == ts.value[i]) printf("%d ", i);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u,v,cost;
        scanf("%d %d %d", &u, &v, &cost);
        graph[i] = makeEdge(u,v,cost,i);        
    }
    sort(graph + 1,graph + n,cmp);
    solve();
}