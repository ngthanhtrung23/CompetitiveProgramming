
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
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
    vector< vector<int> > ke;

    Matching(int n) : n(n), matchL(n+1), matchR(n+1), dist(n+1), seen(n+1, false), ke(n+1) {}

    void addEdge(int u, int v) {
        ke[u].push_back(v);
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

const int MN = 511;

int n, m, p[MN];
int c[MN][MN], t[MN][MN];

struct Flight {
    int s, f, t;
} flight[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> m) {
        FOR(i,1,n) cin >> p[i];
        FOR(i,1,n) FOR(j,1,n) {
            cin >> c[i][j];
            t[i][j] = c[i][j];
            if (i != j) c[i][j] += p[j];
        }
        FOR(k,1,n)
            FOR(i,1,n) FOR(j,1,n)
                c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

        FOR(i,1,m) cin >> flight[i].s >> flight[i].f >> flight[i].t;

        int res = m;
        Matching mat(m);
        FOR(i,1,m) FOR(j,1,m) if (i != j) {
            int u = flight[i].s, v = flight[i].f;
            int x = flight[j].s, y = flight[j].f;

            int toV = flight[i].t + t[u][v] + p[v];
            int toX = toV + c[v][x];
            if (toX <= flight[j].t) {
                mat.addEdge(i, j);
            }
        }
        res -= mat.match();
        cout << res << endl;
    }
}
