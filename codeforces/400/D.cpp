#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
int n, m, k, c[MN], id[MN];
int d[511][511];
vector<int> adj[MN];
bool visited[MN];

bool check() {
    FOR(i,1,k) {
        memset(visited, false, sizeof visited);
        int x = c[i-1] + 1;
        queue<int> qu;
        qu.push(x);
        visited[x] = true;
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(int v : adj[u]) {
                if (!visited[v]) {
                    qu.push(v);
                    visited[v] = true;
                }
            }
        }
        FOR(y,x+1,c[i])
            if (!visited[y]) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m >> k) {
        FOR(i,1,k) {
            cin >> c[i];
            c[i] += c[i-1];
            FOR(x,c[i-1]+1,c[i]) id[x] = i;
        }
//        PR(id, n);
        FOR(i,1,k) FOR(j,1,k) d[i][j] = (i == j) ? 0 : 1000111000;
        FOR(i,1,n) adj[i].clear();
        while (m--) {
            int u, v, cost; cin >> u >> v >> cost;

            if (cost == 0) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }

            u = id[u], v = id[v];
            d[u][v] = d[v][u] = min(d[u][v], cost);
        }

        if (!check()) {
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;

        FOR(x,1,k)
            FOR(i,1,k) FOR(j,1,k)
                d[i][j] = min(d[i][x] + d[x][j], d[i][j]);
        
        FOR(i,1,k) {
            FOR(j,1,k) {
                if (d[i][j] == 1000111000) d[i][j] = -1;
                cout << d[i][j] << ' ';
            }
            cout << endl;
        }
    }
    return 0;
}

