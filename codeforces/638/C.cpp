
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
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;
int deg[MN];
vector<int> ke[MN];
vector< int > ls[MN];
map<int,int> id[MN];

void dfs(int u, int fu, int last) {
    int c = 0;
    for(int v : ke[u]) {
        if (v == fu) continue;

        ++c; if (c == last) ++c;

        ls[c].push_back(id[u][v]);
        dfs(v, u, c);
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (scanf("%lld", &n) == 1) {
        FOR(i,1,n) {
            ke[i].clear();
            deg[i] = 0;
            id[i].clear();
            ls[i].clear();
        }
        FOR(i,1,n-1) {
            int u, v; scanf("%lld%lld", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
            ++deg[u];
            ++deg[v];

            id[u][v] = i;
            id[v][u] = i;
        }
        int root = 1;
        FOR(i,2,n) if (deg[i] > deg[root]) root = i;

        dfs(root, -1, 0);

        printf("%lld\n", deg[root]);
        FOR(i,1,deg[root]) {
            printf("%lld", SZ(ls[i]));
            for(auto p : ls[i]) printf(" %lld", p);
            puts("");
        }
    }
}
