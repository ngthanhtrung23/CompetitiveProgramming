
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

const int MN = 100111;

vector<int> ke[MN];
int n, m, nComp;

struct Comp {
    int u, diam;
} a[MN];

bool operator < (const Comp& a, const Comp& b) {
    return a.diam > b.diam;
}

int visited[MN], f[MN], tr[MN];

void init() {
    nComp = 0;
    FOR(i,1,n) ke[i].clear();
    memset(visited, 0, sizeof visited);
}

void dfs(int u, int fu, int &best) {
    if (f[u] > f[best]) {
        best = u;
    }
    visited[u] = 1;
    REP(i,SZ(ke[u])) {
        int v = ke[u][i];
        if (v != fu) {
            tr[v] = u;
            f[v] = f[u] + 1;
            dfs(v, u, best);
        }
    }
}

Comp get(int u) {
    int x = u;
    f[u] = 0;
    dfs(u, -1, x);

    int y = x;
    f[x] = 0;
    dfs(x, -1, y);

    Comp res;
    res.diam = f[y];

    int mid = y;
    REP(turn,f[y] / 2) mid = tr[mid];

    res.u = mid;

    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &m) == 2) {
        init();
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            ++u; ++v;

            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        memset(visited, 0, sizeof visited);

        FOR(i,1,n) if (!visited[i]) {
            a[++nComp] = get(i);
        }
        sort(a+1, a+nComp+1);

        if (nComp == 1) {
            cout << a[1].diam << endl;
        }
        else {
//            FOR(i,1,nComp) cout << a[i].diam << ' ' << a[i].u << endl;
            FOR(i,2,nComp) {
                int u = a[1].u, v = a[i].u;
                ke[u].push_back(v);
                ke[v].push_back(u);
            }

            memset(visited, 0, sizeof visited);
            Comp res = get(1);
            cout << res.diam << endl;
        }
    }
}
