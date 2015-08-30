
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

const int MN = 100111;

vector<int> ke[MN];
int n, k;
int f[MN], g[MN], sz[MN];

void dfs(int u) {
    sz[u] = 1;

    vector<pair<int,int> > good;
    for(int v : ke[u]) {
        dfs(v);
        sz[u] += sz[v];

        good.push_back(make_pair(f[v], v));
    }
    sort(good.begin(), good.end());
    reverse(good.begin(), good.end());

    // f: return
    int sum = 1;
    set<int> used;
    REP(i,min(k-1,(int) good.size())) {
        sum += good[i].first;
        used.insert(good[i].second);
    }
    f[u] = sum;
    // g: not return
    g[u] = sum;
    int add = 0;
    for(int v : ke[u]) {
        if (used.count(v)) {
            int t = g[v] - f[v];
            if (good.size() >= k) t += good[k-1].first;
            add = max(add, t);
        }
        else add = max(add, g[v]);
    }
    g[u] += add;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &k) == 2) {
        FOR(i,1,n) {
            ke[i].clear();
            int x; scanf("%d", &x);
            while (x--) {
                int u; scanf("%d", &u);
                ke[i].push_back(u);
            }
        }
        dfs(1);
//        PR(all, n);
//        PR(f, n);
//        PR(g, n);
        cout << max(f[1], g[1]) << endl;
    }
}
