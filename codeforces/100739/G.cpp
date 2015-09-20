
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define SZ(X) ((int) ((X).size()))
#define ll long long
using namespace std;

const int MN = 100111;
int n;                             // number of vertices
vector<int> a[MN];                 // adjacency list
int bridges;

struct Node {
    int nn, count;
    int lazy;
};

Node operator + (const Node& a, const Node& b) {
    Node res;
    res.lazy = 0;
    res.nn = min(a.nn, b.nn);
    res.count = 0;
    if (a.nn == res.nn) res.count += a.count;
    if (b.nn == res.nn) res.count += b.count;

    return res;
}

struct SegmentTree {               // 0-based indices
    vector<Node> x;
    int len;
    SegmentTree(int from, int to) {
        len = to - from + 1;
        x.resize(len * 4 + 11);

        build(1, 1, len);
    }

    void down(int i, int l, int r, int mid) {
        if (x[i].lazy) {
            int t = x[i].lazy;

            x[i<<1].lazy += t;
            x[i<<1].nn += t;

            x[i<<1|1].lazy += t;
            x[i<<1|1].nn += t;

            x[i].lazy = 0;
        }
    }

    void build(int i, int l, int r) {
        x[i].nn = 0;
        x[i].count = r - l + 1;
        x[i].lazy = 0;
        if (l == r) return ;

        int mid = (l + r) >> 1;
        build(i<<1, l, mid);
        build(i<<1|1, mid+1, r);
    }

    void visit(int i, int l, int r, int u, int v, int val) {
        if (v < l || r < u) return ;
        if (u <= l && r <= v) {
            x[i].lazy += val;
            x[i].nn += val;
            return ;
        }
        int mid = (l + r) >> 1;
        down(i, l, r, mid);

        visit(i<<1, l, mid, u, v, val);
        visit(i<<1|1, mid+1, r, u, v, val);

        x[i] = x[i<<1] + x[i<<1|1];
    }

    void update(int from, int to, int val) {
        int cur_zero = (x[1].nn == 0) ? x[1].count : 0;
        bridges -= cur_zero;

        visit(1, 1, len, from+1, to, val);

        cur_zero = (x[1].nn == 0) ? x[1].count : 0;
        bridges += cur_zero;
    }
};

const int MAX_LOG = 18;

int father[MAX_LOG + 1][MN];
struct LCA { // Index from 1
    int depth[MN];

public:
    LCA(int root) {
        depth[root] = 1;
        father[0][root] = -1;
        dfs(root, -1);

        FOR(i,1,MAX_LOG) {
            FOR(u,1,n) { // Change this if index from 0
                if (father[i-1][u] < 0) father[i][u] = -1;
                else father[i][u] = father[i-1][ father[i-1][u] ];
            }
        }
    }

    int get(int u, int v) {
        if (u == v) return u;
        if (depth[u] > depth[v]) swap(u, v);

        if (depth[u] != depth[v]) {
            FORD(i,MAX_LOG,0) {
                int x = father[i][v];
                if (x < 0) continue;
                if (depth[x] >= depth[u]) {
                    v = x;
                }
            }
        }
        if (u == v) return u;

        FORD(i,MAX_LOG,0) {
            if (father[i][u] != father[i][v]) {
                u = father[i][u];
                v = father[i][v];
            }
        }
        return father[0][u];
    }

private:
    void dfs(int u, int fu) {
        for(int v : a[u]) if (v != fu) {
            depth[v] = depth[u] + 1;
            father[0][v] = u;
            dfs(v, u);
        }
    }
};

    int numNode[MN];               // size of T(u)
    int par[MN];                   // u --> parent(u)
    int depth[MN];                 // u --> depth(u)
    int heavyUp[MN];               // = 0 if this is 1st in chain
    int heavyDown[MN];             // next vertex in chain
    int firstOnChain[MN];          // chain --> 1st vertex
    int idChain[MN];               // vertex --> chain
    int posChain[MN];              // vertex --> position in chain
    int sizeChain[MN];             // chain --> its size
    
    int good[MN];

struct HeavyLight {
    int numChain;
    vector<SegmentTree> trees;

public:
    HeavyLight(int root) {
        visit(root);
        initHeavyLight();
    }
    void updateTree(int v, int u, int l, int val) {
//        cout << "Update: " << u << ' ' << v << " (" << l << ")" << endl;
        updateTreeAncestor(v, l, val);
        updateTreeAncestor(u, l, val);
    }
    void updateTreeAncestor(int v, int u, int val) { // u is ancestor of v
        while (1) {
            if (idChain[u] == idChain[v]) {
                trees[idChain[u]].update(posChain[u], posChain[v], val);
                return;
            }
            trees[idChain[v]].update(0, posChain[v], val);

            v = firstOnChain[idChain[v]];
            if (good[v] == 0) --bridges;
            good[v] += val;
            if (good[v] == 0) ++bridges;
            v = par[v];
        }
    }

private:
    void visit(int x) {
        numNode[x] = 1;
        for (auto y : a[x]) {
            if (y == par[x]) continue;
            par[y] = x;
            depth[y] = depth[x] + 1;
            visit(y);
            numNode[x] += numNode[y];
        }
        for (auto y : a[x])
            if (y != par[x] && numNode[y] * 2 >= numNode[x])
                heavyUp[y] = 1, heavyDown[x] = y;
    }
    void initHeavyLight() {
        for (int i = 1; i <= n; i++) {
            int x = i;
            if (heavyUp[x]) continue;

//            cout << "New chain: " << endl;
            firstOnChain[numChain] = x;
            while (x) {
//                cout << x << endl;
                idChain[x] = numChain;
                posChain[x] = sizeChain[numChain]++;
                x = heavyDown[x];
            }
            trees.push_back(SegmentTree(0, sizeChain[numChain++] - 1));
        }
    }
};

int m, eu[MN], ev[MN], ec[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,m) {
            scanf("%d%d%d", &eu[i], &ev[i], &ec[i]);
            if (ec[i] == 0) {
                a[ eu[i] ].push_back(ev[i]);
                a[ ev[i] ].push_back(eu[i]);
            }
        }
        bridges = n-1;
        HeavyLight hld(1);
        LCA lca(1);

        set< pair<int,int> > bad;
        FOR(i,1,m) if (ec[i] == 1) {
            int u = eu[i], v = ev[i];
            int l = lca.get(u, v);

            if (bad.count(make_pair(u, v))) {
                bad.erase(make_pair(u, v));
                bad.erase(make_pair(v, u));

                hld.updateTree(u, v, l, -1);
            }
            else {
                bad.insert(make_pair(u, v));
                bad.insert(make_pair(v, u));

                hld.updateTree(u, v, l, +1);
            }
        }
        printf("%d\n", bridges);

        int q; scanf("%d", &q);
        while (q--) {
            int u, v; scanf("%d%d", &u, &v);
            int l = lca.get(u, v);
            if (bad.count(make_pair(u, v))) {
                bad.erase(make_pair(u, v));
                bad.erase(make_pair(v, u));

                hld.updateTree(u, v, l, -1);
            }
            else {
                bad.insert(make_pair(u, v));
                bad.insert(make_pair(v, u));

                hld.updateTree(u, v, l, +1);
            }
            printf("%d\n", bridges);
        }
    }
}

