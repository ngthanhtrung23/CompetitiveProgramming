#include "bits/stdc++.h"

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
using namespace std;

struct Rect {
    // assumption: x1 <= x2 && y1 <= y2
    int x1, y1, x2, y2;
};

bool intersect(const Rect& a, const Rect& b) {
    if (a.x2 <= b.x1) return false;
    if (b.x2 <= a.x1) return false;
    if (a.y2 <= b.y1) return false;
    if (b.y2 <= a.y1) return false;
    return true;
}

const int MN = 200111;   // 2 * no variables.
int n;
vector<int> g[MN], gt[MN];
vector<bool> used;
vector<int> order, comp;

void dfs1 (int v) {
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs1 (to);
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
char res[MN];

void dfs3(int u) {
    res[u/2] = (u % 2 ? 'Q' : 'K');

    for (int v : g[u]) {
        if (!res[v/2]) dfs3(v);
    }
}

bool bad(int i) {
    used.assign(n, false);
    order.clear();
    dfs1(i);
    return used[i^1];
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // input
    vector<Rect> rects[2];
    int nRect; cin >> nRect;
    REP(i,nRect) {
        int x, y; cin >> x >> y;
        x *= 2; y *= 2;  // so that all coordinates are integers

        int w, h; cin >> w >> h;

        rects[0].push_back({x-w, y-h, x+w, y+h});
        rects[1].push_back({x-h, y-w, x+h, y+w});
    }

    n = 2 * nRect;  // 2 * number of variables.
    used.clear();
    order.clear();
    comp.clear();

    REP(i,n) {
        g[i].clear();
        gt[i].clear();
    }

    auto addEdge = [&] (int u, int v) {
        g[u].push_back(v);
        gt[v].push_back(u);
    };

    // for each condition:
    // u -> v: addEdge(u, v)
    REP(ri,2) REP(i,nRect) REP(rj,2) REP(j,nRect) if (i != j) {
        if (intersect(rects[ri][i], rects[rj][j])) {
            addEdge(2*i + ri, 2*j + 1-rj);
        }
    }

    used.assign (n, false);
    REP(i,n)
        if (!used[i])    dfs1 (i);
    comp.assign (n, -1);
    for (int i=0, j=0; i<n; ++i) {
        int v = order[n-i-1];
        if (comp[v] == -1) dfs2 (v, j++);
    }
    REP(i,n)
        if (comp[i] == comp[i^1]) {
            puts ("No");
            return 0;
        }

    REP(i,n) {
        if (bad(i)) {
            res[i/2] = (i % 2 ? 'K' : 'Q');
        }
    }

    puts("Yes");
    for (int i=0; i<n; i += 2) {
        if (res[i/2]) {
            // cerr << "forced " << i/2 << ' ' << res[i/2] << endl;
            putchar(res[i/2]);
            continue;
        }
        res[i/2] = 'K';
        dfs3(i);
        putchar(res[i/2]);
    }
    puts("");

    return 0;
}
