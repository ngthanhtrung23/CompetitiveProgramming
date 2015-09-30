
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

const int MN = 1011;
int n;
vector<int> ke[MN];

int lab[MN];

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    u = getRoot(u);
    v = getRoot(v);
    if (u == v) return ;
    lab[v] += lab[u];
    lab[u] = v;
}

int d[MN], tr[MN], good[MN];

void dfs(int u, int fu) {
    for(int v : ke[u]) if (v != fu) {
        d[v] = d[u] + 1;
        tr[v] = u;
        dfs(v, u);
    }
}

int farthest(int u) {
    d[u] = 1;
    dfs(u, -1);
    return max_element(d+1, d+n+1) - d;
}

bool check() {
    int u = farthest(1);
    int v = farthest(u);

    FOR(i,1,n) good[i] = false;

    int x = v;
    while (x != u) {
        good[x] = true;
        x = tr[x];
    }
    good[u] = true;

    FOR(i,1,n) if (!good[i]) {
        bool has = false;
        for(int v : ke[i]) if (good[v]) {
            has = true;
            break;
        }
        if (!has) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> n && n) {
        FOR(i,1,n) ke[i].clear();
        memset(lab, -1, sizeof lab);
        int m; cin >> m;

        bool hasCycle = false;
        while (m--) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);

            u = getRoot(u); v = getRoot(v);
            if (u == v) {
                hasCycle = true;
            }
            else merge(u, v);
        }
        int nComp = 0;
        FOR(i,1,n) if (lab[i] < 0) ++nComp;
        if (hasCycle || nComp > 1 || !check()) cout << "Graph " << ++test << " is not a caterpillar.";
        else cout << "Graph " << ++test << " is a caterpillar.";
        cout << endl;
    }
}
