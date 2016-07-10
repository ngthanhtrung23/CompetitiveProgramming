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

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 100111;
int n, m;
vector<int> ke[MN];
int d[MN];

void dfs(int u, int fu) {
    for(int v : ke[u]) {
        if (v == fu) continue;
        d[v] = d[u] + 1;
        dfs(v, u);
    }
}

pair<int,int> get() {
    pair<int,int> res = make_pair(1, d[1]);

    FOR(i,2,n) {
        if (d[i] > res.second) {
            res = make_pair(i, d[i]);
        }
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1 && GI(m) == 1) {
        FOR(i,1,n) ke[i].clear();

        FOR(i,1,m) {
            int u, v; GI(u); GI(v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        int root = 1;
        d[root] = 1;
        dfs(root, -1);
        auto t = get();

        root = t.first;
        memset(d, 0, sizeof d);
        dfs(root, -1);
        t = get();

        cout << t.second << endl;
    }
}
