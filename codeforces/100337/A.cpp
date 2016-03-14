
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int inf = 1000111;
struct Matching {
    int n;
    vector<int> matchL, matchR, dist;
    vector<bool> seen;
    vector< vector<int> > ke, ke2;

    Matching(int n) : n(n), matchL(n+1), matchR(n+1), dist(n+1), seen(n+1, false), ke(n+1), ke2(n+1) {}

    void addEdge(int u, int v) {
        ke[u].push_back(v);
        ke2[v].push_back(u);
    }

    bool bfs() {
        queue<int> qu;
        for(int u = 1; u <= n; ++u)
            if (!matchL[u]) {
                dist[u] = 0;
                qu.push(u);
            } else dist[u] = inf;
        dist[0] = inf;

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v) {
                if (dist[matchR[*v]] == inf) {
                    dist[matchR[*v]] = dist[u] + 1;
                    qu.push(matchR[*v]);
                }
            }
        }
        return dist[0] != inf;
    }

    bool dfs(int u) {
        if (u) {
            for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v)
                if (dist[matchR[*v]] == dist[u] + 1 && dfs(matchR[*v])) {
                    matchL[u] = *v;
                    matchR[*v] = u;
                    return true;
                }
            dist[u] = inf;
            return false;
        }
        return true;
    }

    int match() {
        int res = 0;
        while (bfs()) {
            for(int u = 1; u <= n; ++u)
                if (!matchL[u])
                    if (dfs(u)) ++res;
        }
        return res;
    }
};

int n1, n2, m;
int bad[1011], visited[1011];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    while (cin >> n1 >> n2 >> m) {
        Matching mat(max(n1, n2));
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            mat.addEdge(u, v);
        }
        int t = mat.match();

        memset(bad, 0, sizeof bad);

        // un-match vertex on left side
        FOR(i,1,n1) if (mat.matchL[i] <= 0) bad[i] = true;
        FOR(i,1,n2) if (mat.matchR[i] <= 0) bad[i+n1] = true;

        // from left vertex to left vertex
        memset(visited, 0, sizeof visited);
        queue<int> qu;
        FOR(i,1,n1) if (mat.matchL[i] <= 0) {
            visited[i] = true;
            qu.push(i);
        }
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(int v : mat.ke[u]) {
                int w = mat.matchR[v];
                if (!visited[w]) {
                    visited[w] = true;
                    qu.push(w);
                }
            }
        }
        FOR(i,1,n1) if (visited[i]) bad[i] = true;

        // from right vertex to right vertex
        while (!qu.empty()) qu.pop();
        memset(visited, 0, sizeof visited);
        FOR(i,1,n2) if (mat.matchR[i] <= 0) {
            visited[i] = true;
            qu.push(i);
        }
        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(int v : mat.ke2[u]) {
                int w = mat.matchL[v];
                if (!visited[w]) {
                    visited[w] = true;
                    qu.push(w);
                }
            }
        }
        FOR(i,1,n2) if (visited[i]) bad[i + n1] = true;

        FOR(i,1,n1+n2) bad[i] = !bad[i];

        FOR(i,1,n1) cout << (bad[i] ? 'N' : 'P'); cout << endl;
        FOR(i,n1+1,n1+n2) cout << (bad[i] ? 'N' : 'P'); cout << endl;
    }
}
