
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

const int MN = 200111;

struct Node {
    Node* next;
    int x;

    Node(int x) : x(x), next(NULL) {}
};
Node* f[MN];

struct Edge {
    int u, v;
    ll cost;
    int child;

    int from(int x) {
        if (x == u) return v;
        return u;
    }
} e[MN];

int getIn[MN], getOut[MN], cur;
vector<int> ke[MN];

void dfs(int u, int fu, int prev_edge) {
    if (prev_edge) {
        f[u] = f[fu];
        if (e[prev_edge].cost > 1) {
            Node* t = new Node(prev_edge);
            t->next = f[u];
            f[u] = t;
        }
    }

    getIn[u] = ++cur;

    for(int edge_id : ke[u]) {
        int v = e[edge_id].from(u);
        if (v == fu) continue;

        e[edge_id].child = v;

        dfs(v, u, edge_id);
    }
    getOut[u] = ++cur;
}

bool isAncestor(int x, int u) {
    return getIn[x] <= getIn[u] && getOut[u] <= getOut[x];
}

int main() {
    ios :: sync_with_stdio(false);
    int n, q;
    scanf("%d%d", &n, &q);
    FOR(i,1,n-1) {
        scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].cost);
        ke[ e[i].u ].push_back(i);
        ke[ e[i].v ].push_back(i);
    }
    dfs(1, -1, 0);
    while (q--) {
        int typ; scanf("%d", &typ);
        if (typ == 1) {
            int a, b;
            ll y;
            scanf("%d%d%lld", &a, &b, &y);

            REP(turn,2) {
                int u = (turn == 0) ? a : b;
                Node* p = f[u];
                Node* last = NULL;

                while (p) {
                    int eid = p->x;
                    int x = e[eid].child;

                    if (isAncestor(x, a) && isAncestor(x, b)) break;

                    if (e[eid].cost > 1) {
                        y /= e[eid].cost;
                        if (y == 0) break;
                    }
                    else {
                        if (last == NULL) f[u] = f[u]->next;
                        else {
                            last->next = p->next;
                        }
                    }

                    last = p;
                    p = p->next;
                }
            }
            printf("%lld\n", y);
        }
        else {
            int p;
            ll c;
            scanf("%d%lld", &p, &c);
            e[p].cost = c;
        }
    }
}

