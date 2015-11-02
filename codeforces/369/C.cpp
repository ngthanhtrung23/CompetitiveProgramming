
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

int n, coloredChild[MN];
vector<int> res;
vector< pair<int,int> > ke[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
    memset(coloredChild, 0, sizeof coloredChild);
}

void dfs(int u, int fu, int t) {
    REP(i,SZ(ke[u])) {
        int v = ke[u][i].first;
        if (v == fu) continue;

        dfs(v, u, ke[u][i].second);
        if (coloredChild[v]) coloredChild[u] = 1;
    }

    if (t == 2 && !coloredChild[u]) {
        res.push_back(u);
        coloredChild[u] = 1;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        init();
        FOR(i,1,n-1) {
            int u, v, t; scanf("%d%d%d", &u, &v, &t);
            ke[u].push_back(make_pair(v, t));
            ke[v].push_back(make_pair(u, t));
        }
        res.clear();
        dfs(1, -1, 1);
        printf("%d\n", res.size());
        REP(i,SZ(res)) printf("%d ", res[i]);
        puts("");
    }
}

