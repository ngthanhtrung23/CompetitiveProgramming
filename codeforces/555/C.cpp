
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int INF = 1e9 + 11;
struct Node {
    int left, right;
    int minVal;
} nodes[10111000];
int nNode;
int stRows, stCols;

int createNode() {
    ++nNode;
    nodes[nNode].left = nodes[nNode].right = 0;
    nodes[nNode].minVal = INF;
    return nNode;
}

// get the last position, that has value <= k, in range [u, v]
int getLastLower(int id, int l, int r, int u, int v, int k) {
    if (v < l || r < u) return -1;
    if (nodes[id].minVal > k) return -1;
    if (l == r) return r;

    int mid = (l + r) >> 1;
    int res = -1;
    if (nodes[id].right) res = getLastLower(nodes[id].right, mid+1, r, u, v, k);
    if (res < 0 && nodes[id].left) res = getLastLower(nodes[id].left, l, mid, u, v, k);
    return res;
}

int getFirstLower(int id, int l, int r, int u, int v, int k) {
    if (v < l || r < u) return INF;
    if (nodes[id].minVal > k) return INF;

    int mid = (l + r) >> 1;
    int res = -1;
    if (nodes[id].left) res = getFirstLower(nodes[id].left, l, mid, u, v, k);
    if (res < 0 && nodes[id].right) res = getFirstLower(nodes[id].right, mid+1, r, u, v, k);
    return res;
}

void update(int id, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        nodes[id].minVal = val;
        return ;
    }
    int mid = (l + r) >> 1;
    if (u <= mid) {
        if (!nodes[id].left) nodes[id].left = createNode();
        update(nodes[id].left, l, mid, u, val);
    }
    else {
        if (!nodes[id].right) nodes[id].right = createNode();
        update(nodes[id].right, mid+1, r, u, val);
    }
    nodes[id].minVal = min(nodes[ nodes[id].left ].minVal, nodes[ nodes[id].right ].minVal);
}

int main() {
    ios :: sync_with_stdio(false);
    int n, q;
    nodes[0].minVal = INF;
    while (cin >> n >> q) {
        nNode = 0;
        stRows = createNode();
        stCols = createNode();
        set<int> rows, cols;
        while (q--) {
            char c; int x, y;
            cin >> x >> y >> c;
            if (c == 'U') {
                if (cols.count(x)) {
                    puts("0");
                    continue;
                }
                cols.insert(x);
                int k = getLastLower(stRows, 1, n, 1, y, x);
                if (k < 0) k = 0;

//                cout << "Up: k = " << k << endl;
                printf("%d\n", y - k);

                update(stCols, 1, n, x, k+1);
            }
            else {
                if (rows.count(y)) {
                    puts("0");
                    continue;
                }
                rows.insert(y);
                int k = getLastLower(stCols, 1, n, 1, x, y);
                if (k < 0) k = 0;

//                cout << "Left: k = " << k << endl;
                printf("%d\n", x - k);

                update(stRows, 1, n, y, k + 1);
            }
        }
    }
}

