
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

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 200111;
int n;
vector<int> ke[MN];
char a[MN];
int good[MN];
int perm[MN];
vector<int> res;

void dfs(int u, int fu) {
    if (a[u] == '0') {
        perm[u] = perm[fu];
    }
    else perm[u] = a[u] == '+';

    if (ke[u].empty()) {
        good[u] = perm[u];
        return ;
    }

    good[u] = 1;
    for(auto v : ke[u]) {
        dfs(v, u);
        good[u] = good[u] && good[v];
    }
}

void dfs2(int u) {
    if (good[u]) {
        res.push_back(u);
        return ;
    }
    for(int v : ke[u]) {
        dfs2(v);
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        scanf("%s\n", &a[1]);
//        PR(a, n);

        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; GI(u); GI(v);
            ke[u].push_back(v);
        }
        dfs(1, 0);
//        PR(perm, n);
//        PR(good, n);

        res.clear();
        dfs2(1);
        sort(res.begin(), res.end());
        printf("%lld\n", SZ(res));
        for(int x : res) printf("%lld ", x); puts("");
    }
}
