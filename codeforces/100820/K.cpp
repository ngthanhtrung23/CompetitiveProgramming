
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

const int MN = 33;

int n;
char a[MN][MN];

vector<int> ke[MN*MN];
int deg[MN*MN];
int visited[MN*MN];

int id[MN][MN];
int cntId;

bool outside(int u, int v) {
    return u < 1 || v < 1 || u > n || v > n;
}

bool inside(int u, int v) {
    return !outside(u, v);
}

void dfs(int u, int v, int startu, int startv) {
    id[u][v] = ++cntId;

    for(int di = -2; di <= 2; di += 4)
        for(int dj = -2; dj <= 2; dj += 4)
            if (inside(u + di, v + dj) && id[u+di][v+dj] < 0) {
                if (u+di != startu || v+dj != startv) {
                    if (a[u+di][v+dj] == 'B'
                            || a[u+di][v+dj] == 'W')
                        continue;
                }
                dfs(u + di, v + dj, startu, startv);
            }
}

void addEdge(int u, int v) {
    deg[u]++;
    deg[v]++;
    ke[u].push_back(v);
    ke[v].push_back(u);
}

void dfs2(int u) {
    visited[u] = 1;

    for(int v : ke[u])
        if (!visited[v])
            dfs2(v);
}

bool can(int startu, int startv) {
    memset(id, -1, sizeof id);
    cntId = 0;
    dfs(startu, startv, startu, startv);

//    DEBUG(startu);
//    DEBUG(startv);

    FOR(i,1,cntId) {
        deg[i] = 0;
        ke[i].clear();
    }
    FOR(i,1,n) FOR(j,1,n) if (a[i][j] == 'W') {
        if (id[i-1][j-1] >= 0 && id[i+1][j+1] >= 0) {
            addEdge(id[i-1][j-1], id[i+1][j+1]);
        }
        else if (id[i-1][j+1] >= 0 && id[i+1][j-1] >= 0) {
            addEdge(id[i-1][j+1], id[i+1][j-1]);
        }
        else return false;
    }

    memset(visited, 0, sizeof visited);
    dfs2(id[startu][startv]);
    FOR(i,1,cntId)
        if (deg[i] > 0 && !visited[i]) return false;

    int odd = 0;
    FOR(i,1,cntId)
        if (deg[i] % 2) ++odd;

    if (odd > 2) return false;
    if (odd == 2 && deg[id[startu][startv]] % 2 == 0) return false;

    return true;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];
        vector< pair<int,int> > res;

        FOR(i,1,n) FOR(j,1,n) if (a[i][j] == 'B') {
            if (can(i, j)) res.push_back(make_pair(i, j));
        }

        if (res.empty()) cout << "None" << endl;
        else if (SZ(res) == 1) {
            cout << (char) (res[0].second - 1 + 'a')
                << (n - res[0].first + 1) << endl;
        }
        else cout << "Multiple" << endl;
    }
}
