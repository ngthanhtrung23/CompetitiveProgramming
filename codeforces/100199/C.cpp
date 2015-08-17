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

const int MN = 500111;
vector<int> ke[MN];
int good[MN], hasGrant[MN];

void dfs(int u, int fu) {
    for(int v : ke[u]) {
        dfs(v, u);
    }
    if (!hasGrant[u] && !hasGrant[fu]) {
        hasGrant[fu] = 1;
        good[u] = 1;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("grant.in", "r", stdin);
    freopen("grant.out", "w", stdout);
    int n;
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        memset(good, 0, sizeof good);
        memset(hasGrant, 0, sizeof hasGrant);
        FOR(i,2,n) {
            int fi; cin >> fi;
            ke[fi].push_back(i);
        }
        dfs(1, 0);
        good[1] = 0;
        int res = 0;
        FOR(i,1,n) if (good[i]) ++res;
        printf("%d\n", res * 1000);
        FOR(i,1,n) if (good[i]) printf("%d ", i); puts("");
    }
}
