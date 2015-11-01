
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 100111;

struct Node {
    Node* left;
    Node* right;
    int add;

    Node() {
        add = 0;
        left = right = NULL;
    }
} *all;
Node* each[MN];

Node* build(int l, int r) {
    if (l > r) return NULL;

    if (l == r) {
        Node* res = new Node();
        return res;
    }

    Node* res = new Node();
    int mid = (l + r) >> 1;

    res->left = build(l, mid);
    res->right = build(mid+1, r);
    return res;
}

void update(Node* cur, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        cur->add += val;
        return ;
    }
    int mid = (l + r) >> 1;

    update(cur->left, l, mid, u, v, val);
    update(cur->right, mid+1, r, u, v, val);
}

int get(Node* cur, int l, int r, int u) {
    if (u < l || r < u) return 0;
    if (l == r) return cur->add;

    int mid = (l + r) >> 1;
    return cur->add
        + get(cur->left, l, mid, u)
        + get(cur->right, mid+1, r, u);
}

int n, q;
vector<int> ke[MN];
pair<int,int> chain[MN];
int chainSize[MN];

void reset() {
    FOR(i,1,n) ke[i].clear();
    memset(chain, 0, sizeof chain);
    memset(chainSize, 0, sizeof chainSize);
}

void dfs(int u, int fu, int chainId, int chainPos) {
    chain[u] = make_pair(chainId, chainPos);
    chainSize[chainId]++;

    REP(i,SZ(ke[u])) {
        int v = ke[u][i];
        if (v == fu) continue;

        dfs(v, u, chainId, chainPos + 1);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &q) == 2) {
        reset();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        int nChain = 0;
        REP(i,SZ(ke[1])) {
            int u = ke[1][i];
            ++nChain;
            dfs(u, 1, nChain, 1);
        }
//        FOR(i,1,n) cout << chain[i].first << ' ' << chain[i].second << endl;
//        PR(chainSize, nChain);

        all = build(1, n);
        FOR(i,1,nChain) each[i] = build(1, chainSize[i]);

        int val1 = 0;
        while (q--) {
            int typ; scanf("%d", &typ);
            if (typ == 0) {
                // update
                int v, x, d; scanf("%d%d%d", &v, &x, &d);
                if (v == 1) {
                    update(all, 1, n, 1, d, x);
                    val1 += x;
                }
                else {
                    int pos = chain[v].second;
                    int chainId = chain[v].first;
                    if (pos > d) {
                        update(each[chainId], 1, chainSize[chainId], pos - d, pos + d, x);
                    }
                    else {
                        val1 += x;
                        int left = d - pos;
                        update(all, 1, n, 1, left, x);
                        update(each[chainId], 1, chainSize[chainId], left+1, pos+d, x);
                    }
                }
            }
            else {
                // query
                int v; scanf("%d", &v);
                if (v == 1) {
                    printf("%d\n", val1);
                }
                else {
                    int chainId = chain[v].first;
                    printf("%d\n",
                            get(all, 1, n, chain[v].second)
                            + get(each[chainId], 1, chainSize[chainId], chain[v].second)
                            );
                }
            }
        }
    }
}
