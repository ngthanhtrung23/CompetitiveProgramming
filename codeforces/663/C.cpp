
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

const int MN = 100111;
const int INF = 1e9;
vector< pair<int,int> > ke[MN];
int col[MN];
int st[MN], top;
int m, n;

int dfs(int u, int need) {
    st[++top] = u;

    int res = 1;

    for(auto e : ke[u]) {
        int v = e.first;
        int c = e.second;
        if (col[v] < 0) {
            col[v] = c ^ need ^ col[u];
            if (!dfs(v, need))
                res = 0;
        }
        else {
            if (col[v] != (c ^ need ^ col[u])) {
                res = 0;
            }
        }
        if (res) assert(!(col[u] ^ col[v] ^ c ^ need));
    }
    return res;
}

int solve(int need) {
    memset(col, -1, sizeof col);
    int res = 0;
    FOR(i,1,n) if (col[i] < 0) {
        // try color 0
        col[i] = 0;
        top = 0;
        int f0 = INF;
        if (dfs(i, need)) {
            f0 = 0;
            FOR(id,1,top) f0 += col[st[id]];
        }
        FOR(id,1,top) col[st[id]] = -1;

        // try color 1
        col[i] = 1;
        top = 0;
        int f1 = INF;
        if (dfs(i, need)) {
            f1 = 0;
            FOR(id,1,top) f1 += col[st[id]];
        }
        FOR(id,1,top) col[st[id]] = -1;

        if (f0 == INF && f1 == INF) return INF;

        top = 0;
        if (f0 < f1) {
            res += f0;
            col[i] = 0;
            dfs(i, need);
        }
        else {
            res += f1;
            col[i] = 1;
            dfs(i, need);
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
            int u, v; char col = ' ';
            GI(u);
            GI(v);
            while (col < 'A' || col > 'Z') scanf("%c", &col);

            int t = col == 'B';

            ke[u].emplace_back(v, t);
            ke[v].emplace_back(u, t);
        }
        int s0 = solve(0);
        int s1 = solve(1);

        if (s0 == INF && s1 == INF) {
            cout << -1 << endl;
            continue;
        }

        if (s0 < s1) solve(0);
        else solve(1);

        cout << min(s0, s1) << endl;
        FOR(i,1,n) if (col[i]) cout << i << ' '; cout << endl;
    }
}
