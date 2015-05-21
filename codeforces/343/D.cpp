
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 1000111;

int n, getIn[MN], getOut[MN], cur;
vector<int> ke[MN];

struct Node {
    int fill, empty;
} it[MN * 3];

void dfs(int u, int fu) {
    getIn[u] = ++cur;
    for(int v : ke[u]) {
        if (v == fu) continue;

        dfs(v, u);
    }
    getOut[u] = ++cur;
}

void updateFill(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].fill = val;
        return ;
    }
    int mid = (l + r) >> 1;
    updateFill(i*2, l, mid, u, v, val);
    updateFill(i*2+1, mid+1, r, u, v, val);
}

int getFill(int i, int l, int r, int u) {
    if (u < l || r < u) return 0;
    if (l == r) return it[i].fill;

    int mid = (l + r) >> 1;
    return max(it[i].fill, max(getFill(i*2, l, mid, u), getFill(i*2+1, mid+1, r, u)));
}

void updateEmpty(int i, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i].empty = val;
        return ;
    }
    int mid = (l + r) >> 1;
    updateEmpty(i*2, l, mid, u, val);
    updateEmpty(i*2+1, mid+1, r, u, val);

    it[i].empty = max(it[i*2].empty, it[i*2+1].empty);
}

int getEmpty(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].empty;
    int mid = (l + r) >> 1;
    return max(getEmpty(i*2, l, mid, u, v), getEmpty(i*2+1, mid+1, r, u, v));
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        cur = 0;
        dfs(1, -1);

        int q; cin >> q;
        FOR(time,1,q) {
            int typ, u; cin >> typ >> u;
            if (typ == 1) {
                updateFill(1, 1, cur, getIn[u], getOut[u], time);
            }
            else if (typ == 2) {
                updateEmpty(1, 1, cur, getIn[u], time);
            }
            else if (typ == 3) {
                int lastFill = getFill(1, 1, cur, getIn[u]);
                int lastEmpty = getEmpty(1, 1, cur, getIn[u], getOut[u]);

                if (lastEmpty >= lastFill) puts("0");
                else puts("1");
            }
        }
    }
    return 0;
}
