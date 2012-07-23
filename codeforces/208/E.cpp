#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <queue>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
#define FORD(i,a,b) for(int i=(a), _b=(b); i >= _b; --i)
#define REP(i,a) for(int i = 0, _a=(a); i < _a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const int MN = 200111;

int n, father[22][MN];
vector<int> ke[MN];
vector<int> list[MN];
int first[MN], last[MN], a[MN], now, h[MN];
int cnt[MN];
int res[MN], m;

struct Query {
    int u;
    int ind;

    Query(int u, int ind) : u(u), ind(ind) {}
};
vector<Query> query[MN];

#define _(u) ((u) & (-(u)))

int get(int x) {
    int res = 0;
    while (x > 0) {
        res += cnt[x];
        x -= _(x);
    }
    return res;
}

int update(int x, int k) {
    while (x <= 200000) {
        cnt[x] += k;
        x += _(x);
    }
}

void inp() {
    FOR(i,1,n) {
        int u; scanf("%d", &u);
        ke[u].PB(i);
    }
}

void dfs(int u) {
    list[h[u]].PB(u);
    first[u] = ++now;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        father[0][v] = u;
        h[v] = h[u] + 1;
        dfs(v);
    }
    last[u] = ++now;
}

void initLCA() {
    FOR(i,1,19) FOR(u,1,n) {
        if (father[i-1][u] == 0) father[i][u] = 0;
        else father[i][u] = father[i-1][father[i-1][u]];
    }
}

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))

;
int jump(int u, int k) {
    if (k == 0) return u;
    int res = u;
    REP(i,20) if (CONTAIN(k,i)) {
        res = father[i][res];
    }
    return res;
}

void solve() {
    scanf("%d", &m);
    FOR(i,1,m) {
        int v, p; scanf("%d%d", &v, &p);
        int fp = jump(v, p);
        if (fp == 0) {
            res[i] = 0;
        }
        else {
            int fp1 = jump(v, p-1);
            query[h[v]].PB(Query(fp, i));
            query[h[v]].PB(Query(fp1, -i));
        }
    }
    FOR(h,1,n) {
        REP(i,list[h].size()) {
            int u = list[h][i];
            update(first[u], 1);
        }
        REP(i,query[h].size()) {
            int u = query[h][i].u;
            int ind = query[h][i].ind;
            int v = get(last[u]) - get(first[u]-1);
            if (ind > 0) res[ind] += v - 1;
            
        }
        REP(i,list[h].size()) {
            int u = list[h][i];
            update(first[u], -1);
        }
    }
    FOR(i,1,m) printf("%d ", res[i]); puts("");
}

int main() {
    scanf("%d", &n);
    inp();
    dfs(0);
    initLCA();
    solve();
    return 0;
}
