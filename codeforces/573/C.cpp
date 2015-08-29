
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

const int MN = 100111;

int n;
vector<int> ke[MN];
bool f[6][MN], g[6][MN], father[MN];
int nChild[6][MN];

int getFirst(int nChild, int n1, int n2, int n3, int n4, int n5) {
    if (nChild <= 1 && !n2 && !n3 && !n4 && !n5) return 1;
    if (nChild <= 2 && !n2 && !n3 && !n4 && !n5) return 2;
    if (n3 <= 1 && !n4 && !n5) return 3;
    if (n3 <= 2 && !n4 && !n5) return 4;
    return 5;
}

void dfs1(int u, int fu) {
    for(int v : ke[u]) {
        if (v == fu) continue;

        dfs1(v, u);
        father[v] = u;
        nChild[0][u]++;

        if (f[1][v]) ++nChild[1][u];
        else if (f[2][v]) ++nChild[2][u];
        else if (f[3][v]) ++nChild[3][u];
        else if (f[4][v]) ++nChild[4][u];
        else ++nChild[5][u];
    }

    int ok = getFirst(
            nChild[0][u],
            nChild[1][u],
            nChild[2][u],
            nChild[3][u],
            nChild[4][u],
            nChild[5][u]);
    f[ok][u] = true;
}

void dfs2(int u, int fu) {
    if (u != 1) {
        // first, we need to recalculate f[fu] without u
        int n0 = nChild[0][fu] - 1;
        int n1 = nChild[1][fu] - f[1][u];
        int n2 = nChild[2][fu] - f[2][u];
        int n3 = nChild[3][fu] - f[3][u];
        int n4 = nChild[4][fu] - f[4][u];
        int n5 = nChild[5][fu] - f[5][u];

        if (fu != 1) {
            ++n0;
            if (g[1][fu]) ++n1;
            if (g[2][fu]) ++n2;
            if (g[3][fu]) ++n3;
            if (g[4][fu]) ++n4;
            if (g[5][fu]) ++n5;
        }

        int without = getFirst(
                n0,n1,n2,n3,n4,n5);
        g[without][u] = true;
    }
    else {
        g[1][u] = true;
    }

    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs2(v, u);
    }
}

bool solve() {
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    memset(nChild, 0, sizeof nChild);
    dfs1(1, -1);
//    PR(f[1], n);
//    PR(f[2], n);
//    PR(f[3], n);
//    PR(f[4], n);
//    PR(f[5], n);
    if (f[1][1] || f[2][1] || f[3][1] || f[4][1]) return true;
    dfs2(1, -1);
//    PR(g[1], n);
//    PR(g[2], n);
//    PR(g[3], n);
//    PR(g[4], n);
//    PR(g[5], n);

    FOR(i,2,n) {
        int root = getFirst(
            nChild[0][i] + 1,
            nChild[1][i] + g[1][i],
            nChild[2][i] + g[2][i],
            nChild[3][i] + g[3][i],
            nChild[4][i] + g[4][i],
            nChild[5][i] + g[5][i]
        );
        if (root < 5) {
//            DEBUG(i);
            return true;
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        cout << (solve() ? "Yes" : "No") << endl;
    }
}

