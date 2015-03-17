
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

struct Edge {
    int to;
    list<Edge>::iterator rev;

    Edge(int to) :to(to) {}
};

list<Edge> adj[MN];
vector<int> path; // our result

void find_path(int v) {
    while(adj[v].size() > 0) {
        int vn = adj[v].front().to;
        adj[vn].erase(adj[v].front().rev);
        adj[v].pop_front();
        find_path(vn);
    }
    path.push_back(v);
}

void add_edge(int a, int b) {
    adj[a].push_front(Edge(b));
    auto ita = adj[a].begin();
    adj[b].push_front(Edge(a));
    auto itb = adj[b].begin();
    ita->rev = itb;
    itb->rev = ita;
}

int deg[MN];

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) adj[i].clear();
        path.clear();
        memset(deg, 0, sizeof deg);

        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            add_edge(u, v);
            deg[u]++;
            deg[v]++;
        }

        int last = -1;
        FOR(i,1,n) if (deg[i] % 2 == 1) {
            if (last == -1) last = i;
            else {
                add_edge(last, i);
                last = -1;
                ++m;
            }
        }
        if (m % 2) {
            add_edge(1, 1);
            ++m;
        }
        find_path(1);

//        PR0(path, path.size());
        cout << m << endl;
        for(int i = 0; i < path.size() - 1; i += 2) {
            int x = path[i];
            int y = path[(i+1) % path.size()];
            int z = path[(i+2) % path.size()];

            printf("%d %d\n", x, y);
            printf("%d %d\n", z, y);
        }
    }
    return 0;
}

