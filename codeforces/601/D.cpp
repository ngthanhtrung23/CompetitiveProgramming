
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 300111;
const ll MOD = 1e9 + 7;

struct Hash {
    ll x, y;

    Hash() { x = y = 0; }
    Hash(ll x, ll y) : x(x), y(y) {}

    Hash operator * (int k) {
        return Hash(x*k, y*k % MOD);
    }
    Hash operator + (const Hash& a) {
        return Hash(x+a.x, (y+a.y) % MOD);
    }
} p[MN], h[MN];

bool operator < (const Hash& a, const Hash& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

vector<int> ke[MN];
int cost[MN];
int a[MN];
set< Hash > all[MN];
int id[MN], n, nId;

int best = 0, cnt = 0;

void init() {
    p[0] = Hash(1, 1);
    FOR(i,1,MN-1) p[i] = p[i-1] * 31;
}

void dfs1(int u, int fu, int height) {
    h[u] = p[height] * a[u] + h[fu];

    for(int v : ke[u]) {
        if (v == fu) continue;

        dfs1(v, u, height + 1);
    }
}

void dfs2(int u, int fu) {
    id[u] = -1;
    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs2(v, u);
        
        if (id[u] < 0 || SZ(all[id[u]]) < SZ(all[id[v]])) {
            id[u] = id[v];
        }
    }
    if (id[u] < 0) {
        ++nId;
        id[u] = nId;
    }
    all[id[u]].insert(h[u]);
    for(int v : ke[u]) {
        if (v == fu) continue;
        if (id[v] != id[u]) {
            all[id[u]].insert(all[id[v]].begin(), all[id[v]].end());
        }
    }
    int cur = SZ(all[id[u]]) + cost[u];
    if (cur > best) {
        best = cur;
        cnt = 1;
    }
    else if (cur == best) {
        ++cnt;
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    init();
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &cost[i]);
        FOR(i,1,n) all[i].clear();
        FOR(i,1,n) {
            char c = ' ';
            while (c < 'a' || c > 'z') scanf("%c", &c);
            a[i] = c - 'a' + 1;
        }
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
//        PR(cost, n);
//        PR(a, n);
        dfs1(1, 0, 1);

        nId = 0;
        best = 0; cnt = 0;
        dfs2(1, 0);
        cout << best << endl << cnt << endl;
    }
}
