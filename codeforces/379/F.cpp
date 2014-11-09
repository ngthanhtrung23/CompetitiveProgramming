#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 1000111;
vector<int> ke[MN];
int n, queries[MN];
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

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int q; 
    while (cin >> q) {
        n = 4 + 2 * q;
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,4) ke[1].push_back(i);

        FOR(i,1,q) cin >> queries[i];

        int cur = 4;
        FOR(i,1,q) {
            REP(turn,2) {
                ke[queries[i]].push_back(++cur);
            }
        }
        h[1] = 1;
        memset(father, 0, sizeof father);
        dfs(1);
        init();

        int x = 2, y = 3, diam = 2;
        cur = 4;
        FOR(i,1,q) REP(turn,2) {
            int u = ++cur;
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
            if (turn == 1) cout << diam << "\n";
        }
    }
    return 0;
}

