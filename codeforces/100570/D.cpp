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

const int MN = 400111;
long long cx[MN], cy[MN], sx, sy;

struct Query {
    long long x, y;
    int from, to;
} queries[MN];
int n;

void RR() {
    sx = 0;
    FOR(i,1,n) cx[++sx] = queries[i].x;
    sort(cx+1, cx+sx+1);
    sx = unique(cx+1, cx+sx+1) - cx - 1;
    FOR(i,1,n) queries[i].x = lower_bound(cx+1, cx+sx+1, queries[i].x) - cx - 1;

    sy = 0;
    FOR(i,1,n) cy[++sy] = queries[i].y;
    sort(cy+1, cy+sy+1);
    sy = unique(cy+1, cy+sy+1) - cy - 1;
    FOR(i,1,n) queries[i].y = lower_bound(cy+1, cy+sy+1, queries[i].y) - cy - 1;
}

vector < vector<int> > g, gt;
vector<bool> used;
vector<int> order, comp;

void dfs1 (int v) {
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to]) {
            dfs1 (to);
        }
    }
    order.push_back (v);
}
void dfs2 (int v, int cl) {
    comp[v] = cl;
    for (size_t i=0; i<gt[v].size(); ++i) {
        int to = gt[v][i];
        if (comp[to] == -1)
            dfs2 (to, cl);
        }
}
void addEdge(int u, int v) {
    g[u].push_back(v);
    g[v^1].push_back(u^1);
    gt[v].push_back(u);
    gt[u^1].push_back(v^1);
}
bool check(int q) {
//    DEBUG(q);
    int n = 2 * (sx + sy);
    g.resize(n); gt.resize(n);
    REP(i,n) {
        g[i].clear();
        gt[i].clear();
    }
    used.resize(n);
    order.clear();
    comp.resize(n);

    FOR(i,1,q) {
        if (queries[i].from == queries[i].to) {
            addEdge(queries[i].x * 2 + 1, (sx + queries[i].y) * 2 + 1);
            addEdge(queries[i].x * 2, (sx + queries[i].y) * 2);
        }
        else {
            addEdge(queries[i].x * 2, (sx + queries[i].y) * 2 + 1);
            addEdge(queries[i].x * 2 + 1, (sx + queries[i].y) * 2);
        }
    }
    used.assign (n, false);
    REP(i,n)
        if (!used[i]) dfs1(i);
    comp.assign (n, -1);
    for (int i=0, j=0; i<n; ++i) {
        int v = order[n-i-1];
        if (comp[v] == -1) dfs2 (v, j++);
    }
    REP(i,n)
        if (comp[i] >= 0 && comp[i] == comp[i^1]) {
            return false;
        }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> queries[i].x >> queries[i].y;
            cin >> queries[i].from >> queries[i].to;
        }
        RR();
//        DEBUG(sx);
//        DEBUG(sy);

        int l = 0, r = n, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                l = mid + 1;
                res = mid;
            }
            else r = mid - 1;
        }
        FOR(i,1,res) puts("Yes");
        FOR(i,res+1,n) puts("No");
    }
    return 0;
}
