#include <bits/stdc++.h>
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

const int MN = 200111;
int n, queries[MN];
vector<int> ke[MN];

int father[22][MN], h[MN];

void dfs(int u) {
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        h[v] = h[u] + 1;
        father[0][v] = u;
        dfs(v);
    }
}
void init() {
    FOR(lg,1,20) {
        FOR(u,1,n) {
            int x = father[lg-1][u];
            father[lg][u] = father[lg-1][x];
        }
    }
}
int getDist(int u, int v) {
    if (u == v) return 0;
    if (h[u] > h[v]) swap(u, v);
    // now h[u] <= h[v]
    
    int res = 0;
    if (h[u] < h[v]) {
        FORD(i,20,0) {
            int x = father[i][v];
            if (h[x] >= h[u]) {
                v = x;
                res += 1<<i;
            }
        }
    }
    if (u == v) return res;

    FORD(i,20,0)
        if (father[i][u] != father[i][v]) {
            u = father[i][u];
            v = father[i][v];
            res += 1 << (i+1);
        }
    if (u != v) {
        res += 2;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            GI(queries[i]);
            ke[queries[i]].push_back(i);
        }
        h[1] = 1;
        memset(father, 0, sizeof father);
        dfs(1);
        init();
        
        int x = 1, y = 1, diam = 0;
        FOR(u,2,n) {
            int dx = getDist(u, x);
            int dy = getDist(u, y);

            if (dx >= dy && dx > diam) {
                diam = dx;
                y = u;
            }
            else if (dy > dx && dy > diam) {
                diam = dy;
                x = u;
            }
            printf("%lld ", diam);
        }
        puts("");
    }
}
