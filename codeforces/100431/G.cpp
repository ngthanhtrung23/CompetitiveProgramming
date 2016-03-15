#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }
#define SZ(X) ((int) (X).size())
using namespace std;

const int MN = 200111;

struct Node {
    int value;
    vector<int> ke;
    vector<int> versions;
} nodes[MN];

struct Query {
    int op;
    int v;
    int val;
} queries[MN];

int q, nNode;
int ver[MN], dist[MN], front[MN];
vector<int> cur;

int createNode(int value) {
    int res = ++nNode;
    nodes[res].value = value;
    nodes[res].ke.clear();
    return res;
}

void dfs(int u) {
    cur.push_back(u);

    for(int v : nodes[u].versions) {
        int t = SZ(cur) - dist[v];

        if (t >= 0 && t < SZ(cur)) {
            front[v] = nodes[cur[t]].value;
        }
    }

    for(int v : nodes[u].ke) {
        dfs(v);
    }
    cur.pop_back();
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
    while (scanf("%d", &q) == 1) {
        FOR(i,1,q) {
            scanf("%d%d", &queries[i].op, &queries[i].v);
            if (queries[i].op == 1) scanf("%d", &queries[i].val);
        }
        FOR(i,1,q) {
            if (queries[i].op == 1) {
                int u = ver[queries[i].v];
                ver[i] = createNode(queries[i].val);

                nodes[u].ke.push_back(ver[i]);
                dist[i] = dist[ queries[i].v ] + 1;
            }
            else {
                ver[i] = ver[queries[i].v];
                dist[i] = dist[ queries[i].v ] - 1;
            }

            nodes[ver[i]].versions.push_back(i);
        }

        dfs(0);
        FOR(i,1,q) if (queries[i].op == -1) printf("%d\n", front[queries[i].v]);
    }
}
