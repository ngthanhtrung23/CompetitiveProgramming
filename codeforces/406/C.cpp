#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

int n, m;
vector< pair<int,int> > ke[MN];
bool visited[MN], used[MN];

map<pair<int,int>, int> id;

int cur;
pair<pair<int,int>,int> res[MN];

void dfs(int u, int prev) {
    visited[u] = true;
    int last = -1;

    REP(i,ke[u].size()) {
        int v = ke[u][i].first;
        if (v == prev) continue;

        if (used[id[make_pair(u, v)]]) continue;

        if (!visited[v]) {
            dfs(v, u);
        }

        if (!used[id[make_pair(u, v)]]) {
            if (last == -1) last = v;
            else {
                res[++cur] = make_pair(make_pair(last, u), v);
                used[id[make_pair(u, last)]] = true;
                used[id[make_pair(u, v)]] = true;
                last = -1;
            }
        }
    }

    if (last > 0 && !used[id[make_pair(u, prev)]]) {
        res[++cur] = make_pair(make_pair(last, u), prev);
        used[id[make_pair(u, last)]] = true;
        used[id[make_pair(u, prev)]] = true;
        last = -1;
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) ke[i].clear();
        id.clear();

        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(make_pair(v, i));
            ke[v].push_back(make_pair(u, i));

            id[make_pair(u, v)] = i;
            id[make_pair(v, u)] = i;
        }

        if (m % 2 == 1) {
            puts("No solution");
        }
        else {
            memset(used, false, sizeof used);
            memset(visited, false, sizeof visited);
            cur = 0;

            dfs(1, -1);
            FOR(i,1,m/2)
                printf("%d %d %d\n", res[i].first.first, res[i].first.second, res[i].second);
        }
    }
    return 0;
}
