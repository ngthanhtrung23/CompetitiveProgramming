#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,a) for(int i = 0; i < a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(x,n) cout << #x << " = "; FOR(__,1,n) cout << x[__] << ' '; puts("");
#define PR0(x,n) cout << #x << " = "; REP(__,n) cout << x[__] << ' '; puts("");
#define ll long long
using namespace std;

struct Point {
    int x, y;
    int index;
    Point() { x = y = 0; }
    Point(int x, int y, int index) : x(x), y(y), index(index) {}

} a[1511];

inline int ccw(const Point &a, const Point &b, const Point &c) {
    long long t = (b.x-a.x)*(ll)(c.y-a.y) - (b.y-a.y)*(ll)(c.x-a.x);
    if (t == 0) return 0;
    else if (t < 0) return -1;
    else return 1;
}

Point pivot;
inline bool operator < (const Point &a, const Point &b) {
    return ccw(pivot, a, b) == 1;
}

vector<int> ke[1511];
int res[1511], n, sz[1511];

void dfs(int u, int fu = -1) {
    sz[u] = 1;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void solve(int root, int fat, int l, int r) {
    pivot = a[l];
    sort(a+l+1, a+r+1);
    // cout << "solve: " << root << ": ";
    // FOR(i,l,r) cout << a[i].index << ' '; puts("");

    res[a[l].index] = root;

    int now = l+1;
    REP(i,ke[root].size()) {
        int v = ke[root][i];
        if (v == fat) continue;

        solve(v, root, now, now+sz[v]-1);
        now = now + sz[v];
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();
        memset(res, 0, sizeof res);

        FOR(i,1,n-1) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(v);
            ke[v].PB(u);
        }
        FOR(i,1,n) {
            int x, y; scanf("%d%d", &x, &y);
            a[i] = Point(x, y, i);
        }
        int save = 1;
        FOR(i,1,n)
            if (a[i].y < a[save].y || (a[i].y == a[save].y && a[i].x < a[save].x)) save = i;

        swap(a[save], a[1]);
        pivot = a[1];
        sort(a+2, a+n+1);

        dfs(1);
        solve(1, -1, 1, n);

        FOR(i,1,n) printf("%d ", res[i]); puts("");
    }
    return 0;
}
