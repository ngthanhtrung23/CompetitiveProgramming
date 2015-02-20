
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

const int MN = 100111;
vector<int> g[MN];
int n, q;


const int MAXLIST = MN * 2;
const int LOG_MAXLIST = 18;
const int SQRT_MAXLIST = 447;
const int MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1;
int h[MN]; // vertex height
vector<int> a; // dfs list
int a_pos[MN]; // positions in dfs list
int block; // block size = 0.5 log A.size()
int bt[MAXBLOCKS][LOG_MAXLIST+1]; // sparse table on blocks (relative minimum positions in blocks)
int bhash[MAXBLOCKS]; // block hashes
int brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2]; // rmq inside each block, indexed by block hash
int log2_[2*MN]; // precalced logarithms (floored values)

void dfs(int v, int curh) {
    h[v] = curh;
    a_pos[v] = (int)a.size();
    a.push_back (v);
    for (size_t i=0; i<g[v].size(); ++i)
        if (h[g[v][i]] == -1) {
            dfs (g[v][i], curh+1);
            a.push_back (v);
        }
}

int log (int n) {
    int res = 1;
    while (1<<res < n)  ++res;
    return res;
}

// compares two indices in a
inline int min_h (int i, int j) {
    return h[a[i]] < h[a[j]] ? i : j;
}

// O(N) preprocessing
void build_lca() {
    int sz = (int)a.size();
    block = (log(sz) + 1) / 2;
    int blocks = sz / block + (sz % block ? 1 : 0);

    // precalc in each block and build sparse table
    memset (bt, 255, sizeof bt);
    for (int i=0, bl=0, j=0; i<sz; ++i, ++j) {
        if (j == block)
            j = 0,  ++bl;
        if (bt[bl][0] == -1 || min_h (i, bt[bl][0]) == i)
            bt[bl][0] = i;
    }
    for (int j=1; j<=log(sz); ++j)
        for (int i=0; i<blocks; ++i) {
            int ni = i + (1<<(j-1));
            if (ni >= blocks)
                bt[i][j] = bt[i][j-1];
            else
                bt[i][j] = min_h (bt[i][j-1], bt[ni][j-1]);
        }

    // calc hashes of blocks
    memset (bhash, 0, sizeof bhash);
    for (int i=0, bl=0, j=0; i<sz||j<block; ++i, ++j) {
        if (j == block)
            j = 0,  ++bl;
        if (j > 0 && (i >= sz || min_h (i-1, i) == i-1))
            bhash[bl] += 1<<(j-1);
    }

    // precalc RMQ inside each unique block
    memset (brmq, 255, sizeof brmq);
    for (int i=0; i<blocks; ++i) {
        int id = bhash[i];
        if (brmq[id][0][0] != -1)  continue;
        for (int l=0; l<block; ++l) {
            brmq[id][l][l] = l;
            for (int r=l+1; r<block; ++r) {
                brmq[id][l][r] = brmq[id][l][r-1];
                if (i*block+r < sz)
                    brmq[id][l][r] =
                        min_h (i*block+brmq[id][l][r], i*block+r) - i*block;
            }
        }
    }

    // precalc logarithms
    for (int i=0, j=0; i<sz; ++i) {
        if (1<<(j+1) <= i)  ++j;
        log2_[i] = j;
    }
}

// answers RMQ in block #bl [l;r] in O(1)
inline int lca_in_block (int bl, int l, int r) {
    return brmq[bhash[bl]][l][r] + bl*block;
}

// answers LCA in O(1)
int lca (int v1, int v2) {
    int l = a_pos[v1],  r = a_pos[v2];
    if (l > r)  swap (l, r);
    int bl = l/block,  br = r/block;
    if (bl == br)
        return a[lca_in_block(bl,l%block,r%block)];
    int ans1 = lca_in_block(bl,l%block,block-1);
    int ans2 = lca_in_block(br,0,r%block);
    int ans = min_h (ans1, ans2);
    if (bl < br - 1) {
        int pw2 = log2_[br-bl-1];
        int ans3 = bt[bl+1][pw2];
        int ans4 = bt[br-(1<<pw2)][pw2];
        ans = min_h (ans, min_h (ans3, ans4));
    }
    return a[ans];
}
const int T = 300;
int qu[MN], first, last;
int visited[MN], f[MN];

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        vector<int> reds;
        FOR(i,1,n) g[i].clear();

        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        memset(h, -1, sizeof h);
        h[1] = 1;
        dfs(1, 1);
        build_lca();

        reds.push_back(1);
        FOR(i,1,n) f[i] = visited[i] = MN;

        while (q--) {
            int typ, u; scanf("%d%d", &typ, &u);
            if (typ == 1) {
                reds.push_back(u);
                if (reds.size() == T) {
                    FOR(i,1,n) visited[i] = MN;

                    first = 1; last = 0;
                    for(int x : reds) {
                        qu[++last] = x;
                        visited[x] = 0;
                    }

                    while (first <= last) {
                        int u = qu[first++];
                        for(int v : g[u]) {
                            if (MN == visited[v]) {
                                qu[++last] = v;
                                visited[v] = visited[u] + 1;
                            }
                        }
                    }
                    reds.clear();

                    FOR(i,1,n) f[i] = min(f[i], visited[i]);
                }
            }
            else {
                int res = f[u];
                for(int x : reds) {
                    int l = lca(x, u);
                    res = min(res, h[x] + h[u] - h[l] - h[l]);
                }
                printf("%d\n", res);
            }
        }
    }
    return 0;
}
