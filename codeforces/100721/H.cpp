
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

const int MN = 511;

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

int h[MN], id[MN];
char gender[MN];
string music[MN], sport[MN];

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        int nAll, nMale, nFemale;
        cin >> nAll;
        nMale = nFemale = 0;
        FOR(i,1,nAll) {
            cin >> h[i] >> gender[i] >> music[i] >> sport[i];
            if (gender[i] == 'M') {
                ++nMale;
                id[i] = nMale;
            }
            else {
                ++nFemale;
                id[i] = nFemale;
            }
        }

        Matching match(max(nMale, nFemale));
        FOR(i,1,nAll) if (gender[i] == 'M')
            FOR(j,1,nAll) if (gender[j] == 'F') {
                if (abs(h[i] - h[j]) <= 40 && music[i] == music[j] && sport[i] != sport[j]) {
                    match.addEdge(id[i], id[j]);
                }
            }

        cout << nFemale + nMale - match.match() << endl;
    }
}
