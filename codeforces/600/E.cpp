
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

const int MN = 200111;

struct CNT {
    map<int,int> cnt;
    int ln;
    ll sum;

    void init() {
        cnt.clear();
        ln = -1;
        sum = 0;
    }

    void add(int c, int x) {
        cnt[c] += x;
        if (cnt[c] > ln) {
            ln = cnt[c];
            sum = c;
        }
        else if (cnt[c] == ln) {
            sum += c;
        }
    }
} cnt[MN];
int id[MN], color[MN], n, nId;
vector<int> ke[MN];
ll res[MN];

void dfs(int u, int fu) {
    int best = -1;
    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs(v, u);

        if (best < 0 || cnt[id[v]].cnt.size() > cnt[best].cnt.size())
            best = id[v];
    }
    if (best < 0) {
        best = ++nId;
    }
    id[u] = best;

    cnt[id[u]].add(color[u], 1);

    for(int v : ke[u]) {
        if (v == fu) continue;
        if (id[v] == id[u]) continue;

        for(auto p : cnt[id[v]].cnt)
            cnt[id[u]].add(p.first, p.second);
    }
    res[u] = cnt[id[u]].sum;
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &color[i]);
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        FOR(i,1,n) cnt[i].init();
        nId = 0;
        dfs(1, -1);
        FOR(i,1,n) printf("%lld ", res[i]);
        puts("");
    }
}
