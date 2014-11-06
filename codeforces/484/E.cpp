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

const int MN = 100111;

struct Node {
    int len, suff, pref, all;
    int left, right;
} it[10111000];
int a[MN], c[MN];
int n, s, nNodes;
pair<int,int> x[MN];
int root[MN];

void refine(int node) {
    int l = it[node].left, r = it[node].right;
    it[node].len = it[l].len + it[r].len;
    it[node].suff = max(it[r].suff, (it[r].all == it[r].len) ? (it[r].len + it[l].suff) : 0);
    it[node].pref = max(it[l].pref, (it[l].all == it[l].len) ? (it[l].len + it[r].pref) : 0);
    it[node].all  = max(max(it[l].all, it[r].all), it[l].suff + it[r].pref);
}

int update(int node, int l, int r, int u) {
    if (u < l || r < u) return node;
    if (l == r) {
        ++nNodes;
        it[nNodes].len = it[nNodes].suff = it[nNodes].pref = it[nNodes].all = 1;
        it[nNodes].left = it[nNodes].right = 0;
        return nNodes;
    }
    int mid = (l + r) >> 1;
    int x = ++nNodes;
    it[x].left = update(it[node].left, l, mid, u);
    it[x].right = update(it[node].right, mid+1, r, u);
    refine(x);
    return x;
}

int buildTree(int l, int r) {
    if (l == r) {
        ++nNodes;
        it[nNodes].len = 1;
        it[nNodes].suff = it[nNodes].pref = it[nNodes].all = 0;
        it[nNodes].left = it[nNodes].right = 0;
        return nNodes;
    }
    int mid = (l + r) >> 1;
    int u = ++nNodes;
    it[u].left = buildTree(l, mid);
    it[u].right = buildTree(mid+1, r);
    refine(u);
    return u;
}

int top;
Node nodes[1011];

void visit(int p, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        nodes[++top] = it[p];
        return ;
    }
    int mid = (l + r) >> 1;
    visit(it[p].left, l, mid, u, v);
    visit(it[p].right, mid+1, r, u, v);
}

int dp() {
    int res = 0, suff = 0;
    FOR(i,1,top) {
        res = max(res, nodes[i].all);
        res = max(res, suff + nodes[i].pref);
        suff = max(nodes[i].suff, (nodes[i].len == nodes[i].all) ? (nodes[i].all + suff) : 0);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) c[i] = a[i];
        sort(c+1, c+n+1);
        s = unique(c+1, c+n+1) - c - 1;
        FOR(i,1,n) a[i] = lower_bound(c+1, c+s+1, a[i]) - c;

        // PR(a, n);
        FOR(i,1,n) x[i] = make_pair(a[i], i);
        sort(x+1, x+n+1);

        int current;
        nNodes = 0;
        memset(it, 0, sizeof it);
        current = buildTree(1, n);
        // print(current, 1, n);

        memset(root, 0, sizeof root);
        FORD(i,n,1) {
            // cout << x[i].first << ' ' << x[i].second << endl;
            root[x[i].first] = update(current, 1, n, x[i].second);
            current = root[x[i].first];
            // print(current, 1, n);
        }
        FORD(i,s,1) if (!root[i]) root[i] = root[i+1];

        int q; cin >> q;
        while (q--) {
            int u, v, w; cin >> u >> v >> w;
            int l = 1, r = s, res = 1;
            while (l <= r) {
                int mid = (l + r) >> 1;

                top = 0;
                visit(root[mid], 1, n, u, v);
                if (dp() >= w) {
                    res = mid;
                    l = mid + 1;
                }
                else r = mid - 1;
            }
            cout << c[res] << "\n";
        }
    }
    return 0;
}
