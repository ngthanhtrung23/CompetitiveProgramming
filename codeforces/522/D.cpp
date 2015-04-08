
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define next __next
using namespace std;

const int MN = 500111;
const int oo = 1000111000;

int n, q, a[MN], next[MN], ver[MN], nNode;
struct Node {
    int left, right, nn;
} nodes[11000111];

int createNode(int value) {
    ++nNode;
    nodes[nNode].left = nodes[nNode].right = 0;
    nodes[nNode].nn = value;
    return nNode;
}

int build(int l, int r) {
    if (l == r) return createNode(oo);
    int mid = (l + r) >> 1;
    int u = createNode(oo);
    nodes[u].left = build(l, mid);
    nodes[u].right = build(mid+1, r);
    return u;
}

int update(int old, int l, int r, int u, int val) {
    if (u < l || r < u) return old;
    if (l == r) {
        return createNode(val);
    }
    int mid = (l + r) >> 1;

    int x = createNode(oo);
    nodes[x].left = update(nodes[old].left, l, mid, u, val);
    nodes[x].right = update(nodes[old].right, mid+1, r, u, val);
    nodes[x].nn = min(nodes[ nodes[x].left ].nn, nodes[ nodes[x].right ].nn);
    return x;
}

int get(int id, int l, int r, int u, int v) {
    if (v < l || r < u) return oo;
    if (u <= l && r <= v) return nodes[id].nn;

    int mid = (l + r) >> 1;
    return min(get(nodes[id].left, l, mid, u, v),
            get(nodes[id].right, mid+1, r, u, v));
}

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        map<int,int> id;
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            if (id.count(a[i])) next[i] = id[a[i]];
            else next[i] = -1;

            id[a[i]] = i;
        }
//        PR(a, n);
//        PR(next, n);

        nNode = 0;
        ver[0] = build(1, n);
        FOR(i,1,n) {
            int u = next[i];
            if (u > 0) {
                ver[i] = update(ver[i-1], 1, n, u, i - u);
            }
            else ver[i] = ver[i-1];
        }
        while (q--) {
            int l, r; scanf("%d%d", &l, &r);
            int res = get(ver[r], 1, n, l, r);
            printf("%d\n", (res == oo) ? -1 : res);
        }
    }
    return 0;
}

