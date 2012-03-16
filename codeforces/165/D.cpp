#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

struct Node {
    int path, pos;
    Node(int path = 0, int pos = 0) : path(path), pos(pos) {}
} a[100111], b[100111];

vector< pair<int,int> > ke[100111];
vector< vector<int> > cnt;

int n, root, npath, sz[100111];

void dfs(int u, int lu, int path, int pos) {
    a[u] = Node(path, pos);
    b[lu] = Node(path, pos);
    sz[path] = pos;
    
    REP(i, ke[u].size()) {
        int v = ke[u][i].F, id = ke[u][i].S;
        if (id == lu) continue;
        dfs(v, id, path, pos + 1);
    }
}

#define _(u) (u&(-u))

void update(int path, int u, int k) {
    while (u <= sz[path]) {
        cnt[path][u] += k;
        u += _(u);
    }
}

int get(int path, int u) {
    int res = 0;
    while (u > 0) {
        res += cnt[path][u];
        u -= _(u);
    }
    return res;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    int u, v;
    FOR(i,1,n-1) {
        scanf("%d%d", &u, &v);
        ke[u].PB(MP(v, i)); ke[v].PB(MP(u, i));
    }
    root = 1;
    FOR(i,2,n) if (ke[i].size() > 2) root = i;
    cnt.resize(ke[root].size() + 2);
    
    REP(i,ke[root].size()) {
        npath++;
        dfs(ke[root][i].F, ke[root][i].S, npath, 1);
        cnt[npath].resize(sz[npath] + 2);
    }
/*    PR(sz, npath);
    
    FOR(i,1,n) cout << a[i].path << ' ' << a[i].pos << endl;
    FOR(i,1,n-1) cout << b[i].path << ' ' << b[i].pos << endl;
*/    
    int q; scanf("%d", &q);
    int x, cur, res;
    while (q--) {
        scanf("%d", &x);
        if (x == 1) {
            scanf("%d", &u);
            update(b[u].path, b[u].pos, -1);
        }
        else if (x == 2) {
            scanf("%d", &u);
            update(b[u].path, b[u].pos, +1);
        }
        else {
            scanf("%d%d", &u, &v);
            if (v == root) swap(u, v);
            if (u == root) {
                cur = get(a[v].path, a[v].pos);
                res = a[v].pos;
            }
            else if (a[u].path == a[v].path) {
                if (a[v].pos > a[u].pos) swap(u, v);
                cur = get(a[u].path, a[u].pos) - get(a[v].path, a[v].pos);
                res = a[u].pos - a[v].pos;
            }
            else {
                cur = get(a[u].path, a[u].pos) + get(a[v].path, a[v].pos);
                res = a[u].pos + a[v].pos;
            }
            if (cur > 0) puts("-1");
            else printf("%d\n", res);
        }
    }
    
    return 0;
}
