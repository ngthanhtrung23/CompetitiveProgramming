#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
using namespace std;

const int MN = 2011;

int lab[MN], d[MN][MN], n, nEdges;
pair<int, pair<int,int> > edges[MN*MN];
vector< pair<int,int> > ke[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
    memset(lab, -1, sizeof lab);
    nEdges = 0;
}

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
}

int visited[MN];
void dfs(int u, int fu) {
    FOR(i,0,-1+ke[u].size()) {
        int v = ke[u][i].first;
        if (v == fu) continue;

        visited[v] = visited[u] + ke[u][i].second;
        dfs(v, u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        init();
        bool ok = true;
        FOR(i,1,n) FOR(j,1,n) {
            cin >> d[i][j];
            if (i != j && !d[i][j]) ok = false;
        }
        if (!ok) {
            cout << "NO" << endl;
            continue;
        }

        nEdges = 0;
        FOR(i,1,n) FOR(j,i+1,n) {
            ++nEdges;
            edges[nEdges] = make_pair(d[i][j], make_pair(i, j));
        }
        sort(edges+1, edges+nEdges+1);

        FOR(i,1,nEdges) {
            int u = edges[i].second.first, v = edges[i].second.second;
            if (getRoot(u) == getRoot(v)) continue;

            merge(u, v);
            ke[u].push_back(make_pair(v, edges[i].first));
            ke[v].push_back(make_pair(u, edges[i].first));
        }
        FOR(i,1,n) {
            memset(visited, 0, sizeof visited);
            dfs(i, -1);

            FOR(j,1,n) if (visited[j] != d[i][j]) ok = false;
        }
        if (ok) cout << "YES"; else cout << "NO";
        cout << endl;
    }
    return 0;
}

