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

const int MN = 2011;

int n, m, s;
struct Edge {
    int u, v;
    ll c;
} e[5011];

vector<int> ke[MN];

ll f[MN];
bool bad[MN];
bool visited[MN], visited2[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
    memset(bad, 0, sizeof bad);
    memset(visited, 0, sizeof visited);
    memset(visited2, 0, sizeof visited2);
}

void dfs(int u) {
    visited[u] = true;

    for(int v : ke[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

void dfs2(int u) {
    visited2[u] = true;
    for(int v : ke[u]) {
        if (!visited2[v]) {
            dfs2(v);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    while (cin >> n >> m >> s) {
        init();
        FOR(i,1,m) {
            cin >> e[i].u >> e[i].v >> e[i].c;
            ke[e[i].u].push_back(e[i].v);
        }
        FOR(i,1,n) f[i] = 2000111000111000111LL;
        f[s] = 0;
        FOR(turn,1,n+1) {
            FOR(i,1,m) {
                int u = e[i].u, v = e[i].v;
                f[v] = min(f[v], f[u] + e[i].c);
            }
        }
        FOR(turn,1,n+1) {
            FOR(i,1,m) {
                int u = e[i].u, v = e[i].v;
                if (f[v] > f[u] + e[i].c) {
                    bad[v] = true;
                    f[v] = f[u] + e[i].c;
                }
            }
        }
//        PR(bad, n);
        dfs(s);
//        PR(visited, n);

        FOR(i,1,n) if (bad[i] && visited[i]) {
            dfs2(i);
        }

        FOR(i,1,n) {
            if (!visited[i]) puts("*");
            else if (visited2[i]) puts("-");
            else printf("%I64d\n", f[i]);
        }
    }
}