
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 5011;

int n;
pair<int,int> a[MN];
vector< pair<int,int> > ke[MN];
pair<int,int> father[MN];

void dfs(int u, int fu) {
    for(auto e : ke[u]) {
        if (e.first == fu) continue;

        father[e.first] = make_pair(u, e.second);
        dfs(e.first, u);
    }
}

int res[MN], pos[MN], used[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) ke[i].clear();

        FOR(i,2,n) {
            int u, v, c; cin >> u >> v >> c;
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }
        dfs(1, -1);

        FOR(i,1,n) pos[i] = i;

        memset(res, 0, sizeof res);
        FOR(turn,1,n) {
            memset(used, 0, sizeof used);

            FOR(i,1,n) {
                int u = a[i].second;
                if (pos[u] != 1) {
                    res[u] = turn;

                    if (used[pos[u]] == father[pos[u]].second) continue;

                    used[pos[u]]++;
                    pos[u] = father[pos[u]].first;
                }
            }
        }
        FOR(i,1,n) cout << res[i] << " \n"[i == n];
    }
    return 0;
}

