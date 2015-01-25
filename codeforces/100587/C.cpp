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

const int MN = 20111;

struct Node {
    int next[30];
    int f[111];
    int good, size;
} nodes[MN];

int root, n, k, nNode;

int addNode() {
    nNode++;
    memset(nodes[nNode].next, 0, sizeof nodes[nNode].next);
    memset(nodes[nNode].f, 0, sizeof nodes[nNode].f);
    nodes[nNode].good = 0;
    nodes[nNode].size = 0;
    return nNode;
}

void update(int& x, int val) {
    x = min(x, val);
}

void dfs1(int u) {
    nodes[u].size = nodes[u].good;
    REP(c,26) {
        int v = nodes[u].next[c];
        if (v == 0) continue;

        dfs1(v);
        nodes[u].size += nodes[v].size;
    }
}

int tmp[111];
void dfs2(int u) {
    FOR(t,1,k) nodes[u].f[t] = 1000111000;
    if (nodes[u].good) nodes[u].f[1] = 0;
    nodes[u].f[0] = 0;

    REP(c,26) {
        int v = nodes[u].next[c];
        if (v == 0) continue;

        dfs2(v);

        FOR(t,0,k) tmp[t] = nodes[u].f[t];

        FOR(a,0,k) FORD(b,k-a,0)
            update(nodes[u].f[a+b], tmp[b] + nodes[v].f[a] + a);
    }
    if (nodes[u].size) nodes[u].f[1] = 0;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);

    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n >> k;
        nNode = 0;

        root = addNode();
        FOR(i,1,n) {
            string s; cin >> s;
            int p = root;
            for(char c : s) {
                int x = c - 'a';
                if (nodes[p].next[x] == 0) {
                    nodes[p].next[x] = addNode();
                }
                p = nodes[p].next[x];
            }
            nodes[p].good = 1;
        }
        dfs1(1);
        dfs2(1);
        cout << "Case #" << test << ": " << max(1, nodes[1].f[k]) << endl;
        cerr << "test = " << test << endl;
    }

    return 0;
}
