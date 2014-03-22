#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

struct Point {
    long long x, y;

    Point() {}
    Point(long long x, long long y) : x(x), y(y) {}

    Point operator - (Point a) { return Point(x-a.x, y-a.y); }
} a[MN];
int ch[MN];

int n;
vector<int> ke[MN];
int father[20][200111], h[200111];

int ccw(Point a, Point b, Point c) {
    b = b - a; c = c - a;
    long long t = b.x*c.y - b.y*c.x;
    if (t == 0) return 0;
    else if (t < 0) return -1;
    else return 1;
}

void dfs(int u, int fu) {
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        father[0][v] = u;
        h[v] = h[u] + 1;
        dfs(v, u);
    }
}

void init() {
    FOR(i,1,19) FOR(u,1,n) {
        int v = father[i-1][u];
        if (v == -1) {
            father[i][u] = -1;
        }
        else {
            father[i][u] = father[i-1][v];
        }
    }
}

int lca(int u, int v) {
    if (h[u] < h[v]) swap(u,v);
    if (h[u] != h[v]) {
        FORD(i,18,0) {
            int x = father[i][u];
            if (x == -1) continue;
            if (h[x] >= h[v]) {
                u = x;
            }
        }
    }

    if (u != v) {
        int uu, vv;
        FORD(i,18,0) {
            uu = father[i][u];
            vv = father[i][v];
            if (uu != vv) {
                u = uu;
                v = vv;
            }
        }
        u = father[0][u];
    }
    return u;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i].x >> a[i].y;
        ke[n-1].push_back(n);
        ke[n].push_back(n-1);

        int top = 2;
        ch[1] = n;
        ch[2] = n-1;
        FORD(i,n-2,1) {
            while (top >= 2 && ccw(a[i], a[ch[top]], a[ch[top-1]]) == 1) {
                --top;
            }
            ke[i].push_back(ch[top]);
            ke[ch[top]].push_back(i);
            ch[++top] = i;
        }

        memset(father, -1, sizeof father);
        dfs(n, -1);
        init();

        int q; cin >> q;
        while (q--) {
            int u, v; cin >> u >> v;
            cout << lca(u, v) << ' ';
        }
        cout << endl;
    }
    return 0;
}
