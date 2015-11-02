
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

int n, deg[MN], nChain;
vector<int> ke[MN];
pair<int,int> chain[MN];
int chainSize[MN];
pair<int,int> edge[MN];

struct Node {
    Node* left;
    Node* right;
    int sum;
};

vector<Node*> it;

Node* build(int l, int r) {
    if (l > r) return NULL;
    if (l == r) {
        Node* res = new Node();
        res->left = res->right = NULL;
        res->sum = 1;
        return res;
    }
    int mid = (l + r) >> 1;
    Node* res = new Node();
    res->sum = r - l + 1;

    res->left = build(l, mid);
    res->right = build(mid+1, r);

    return res;
}

void setVal(Node* cur, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        cur->sum = val;
        return ;
    }
    int mid = (l + r) >> 1;
    setVal(cur->left, l, mid, u, val);
    setVal(cur->right, mid+1, r, u, val);

    cur->sum = cur->left->sum + cur->right->sum;
}

int getSum(Node* cur, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return cur->sum;

    int mid = (l + r) >> 1;
    return getSum(cur->left, l, mid, u, v) + getSum(cur->right, mid+1, r, u, v);
}

void init() {
    FOR(i,1,n) ke[i].clear();
    memset(deg, 0, sizeof deg);
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
    while (scanf("%d", &n) == 1) {
        init();
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
            ke[v].push_back(u);

            deg[u]++;
            deg[v]++;

            edge[i-1] = make_pair(u, v);
        }
        int root = 1;
        FOR(i,2,n) if (deg[i] > deg[root]) root = i;

        REP(i,SZ(ke[root])) {
            int u = ke[root][i];
            ++nChain;
            dfs(u, root, nChain, 1);
        }

        it.resize(nChain + 5);
        FOR(i,1,nChain) it[i] = build(1, chainSize[i]);

        int q; scanf("%d", &q);
        while (q--) {
            int typ; scanf("%d", &typ);
            int u, v;
            if (typ == 1 || typ == 2) {
                int id; scanf("%d", &id);
                u = edge[id].first;
                v = edge[id].second;

                if (chain[u].second < chain[v].second) {
                    swap(u, v);
                }

                int chainId = chain[u].first;
                if (typ == 1) {
                    // paint black
                    setVal(it[chainId], 1, chainSize[chainId], chain[u].second, 1);
                }
                else {
                    // paint white
                    setVal(it[chainId], 1, chainSize[chainId], chain[u].second, 0);
                }
            }
            else {
                // query u --> v
                scanf("%d%d", &u, &v);
                if (chain[u].second < chain[v].second) swap(u, v);
                int chainU = chain[u].first;
                int chainV = chain[v].first;

                if (v == root) {
                    if (getSum(it[chainU], 1, chainSize[chainU], 1, chain[u].second) == chain[u].second) {
                        printf("%d\n", chain[u].second);
                    }
                    else {
                        puts("-1");
                    }
                }
                else if (chainU == chainV) {
                    if (getSum(it[chainU], 1, chainSize[chainU], chain[v].second + 1, chain[u].second)
                            == chain[u].second - chain[v].second) {
                        printf("%d\n", chain[u].second - chain[v].second);
                    }
                    else {
                        puts("-1");
                    }
                }
                else {
                    if (getSum(it[chainU], 1, chainSize[chainU], 1, chain[u].second) == chain[u].second
                            && getSum(it[chainV], 1, chainSize[chainV], 1, chain[v].second) == chain[v].second) {
                        printf("%d\n", chain[u].second + chain[v].second);
                    }
                    else {
                        puts("-1");
                    }
                }
            }
        }
    }
}
