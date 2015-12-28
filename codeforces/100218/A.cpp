#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

int A[5007];
bool adj[5007][5007];

vii adList;

bool check(int u, int v) {
    for(int i=1; i<adList[u].size(); i++) {
        int k = adList[u][i];
        if (!adj[k][v]) return false;
    }
    return true;
}

int main() {
    
    freopen("bombing.in", "r", stdin);
    freopen("bombing.out", "w", stdout);
    
    int n, m, x, y, u, v;
    scanf("%d %d", &n, &m);
    
    bool res = true;
    
    for(int i=1; i<=n; i++) {
        scanf("%d", &x);
        A[x] = i;
    }
    
    adList.assign(n+1, vi());
    
    for(int i=1; i<=m; i++) {
        scanf("%d %d", &x, &y);
        u = A[x]; v = A[y];
        adj[u][v] = adj[v][u] = true;
        if (u < v) adList[u].push_back(v);
        else adList[v].push_back(u);
    }
    
    for(int i=1; i<=n; i++) {
        sort(adList[i].begin(), adList[i].end());
    }
    
    for(int i=1; i<n; i++) {
        if (adList[i].size() > 0) {
            u = adList[i][0];
            res = check(i, u);
        }
        if (!res) break;
    }
    
    if (res) cout << "YES" << endl;
    else cout << "NO" << endl;
}